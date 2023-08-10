#include "AES.h"

AES::AES() {
  blockBytesLen = 4 * 4 * sizeof(unsigned char);
}


unsigned char *AES::EncryptCFB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) const {
  auto out = new unsigned char[inLen];
  auto block = new unsigned char[blockBytesLen];
  auto encryptedBlock = new unsigned char[blockBytesLen];
  auto roundKeys = new unsigned char[4 * 4 * (14 + 1)];
  KeyExpansion(key, roundKeys);
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
    EncryptBlock(block, encryptedBlock, roundKeys);
    XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
    memcpy(block, out + i, blockBytesLen);
  }

  delete[] block;
  delete[] encryptedBlock;
  delete[] roundKeys;

  return out;
}

unsigned char *AES::DecryptCFB(const unsigned char in[], unsigned int inLen,
                               const unsigned char key[],
                               const unsigned char *iv) const {
  auto out = new unsigned char[inLen];
  auto block = new unsigned char[blockBytesLen];
  auto encryptedBlock = new unsigned char[blockBytesLen];
  auto roundKeys = new unsigned char[4 * 4 * (14 + 1)];
  KeyExpansion(key, roundKeys);
  memcpy(block, iv, blockBytesLen);
  for (unsigned int i = 0; i < inLen; i += blockBytesLen) {
    EncryptBlock(block, encryptedBlock, roundKeys);
    XorBlocks(in + i, encryptedBlock, out + i, blockBytesLen);
    memcpy(block, in + i, blockBytesLen);
  }

  delete[] block;
  delete[] encryptedBlock;
  delete[] roundKeys;

  return out;
}

void AES::EncryptBlock(const unsigned char in[], unsigned char out[],
                       unsigned char *roundKeys) {
  auto state = new unsigned char *[4];
  state[0] = new unsigned char[4 * 4];
  int i, j, round;
  for (i = 0; i < 4; i++) {
    state[i] = state[0] + 4 * i;
  }

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      state[i][j] = in[i + 4 * j];
    }
  }

  AddRoundKey(state, roundKeys);

  for (round = 1; round <= 14 - 1; round++) {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, roundKeys + round * 4 * 4);
  }

  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(state, roundKeys + 14 * 4 * 4);

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      out[i + 4 * j] = state[i][j];
    }
  }

  delete[] state[0];
  delete[] state;
}

void AES::SubBytes(unsigned char **state) {
  int i, j;
  unsigned char t;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      t = state[i][j];
      state[i][j] = sbox[t / 16][t % 16];
    }
  }
}

void AES::ShiftRow(unsigned char **state, int i,
                   int n)  // shift row i on n positions
{
  auto tmp = new unsigned char[4];
  for (int j = 0; j < 4; j++) {
    tmp[j] = state[i][(j + n) % 4];
  }
  memcpy(state[i], tmp, 4 * sizeof(unsigned char));

  delete[] tmp;
}

void AES::ShiftRows(unsigned char **state) {
  ShiftRow(state, 1, 1);
  ShiftRow(state, 2, 2);
  ShiftRow(state, 3, 3);
}

unsigned char AES::xtime(unsigned char b)  // multiply on x
{
  return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
}

void AES::MixColumns(unsigned char **state) {
  unsigned char temp_state[4][4];

  for (auto & i : temp_state) {
    memset(i, 0, 4);
  }

  for (size_t i = 0; i < 4; ++i) {
    for (size_t k = 0; k < 4; ++k) {
      for (size_t j = 0; j < 4; ++j) {
        if (CMDS[i][k] == 1)
          temp_state[i][j] ^= state[k][j];
        else
          temp_state[i][j] ^= GF_MUL_TABLE[CMDS[i][k]][state[k][j]];
      }
    }
  }

  for (size_t i = 0; i < 4; ++i) {
    memcpy(state[i], temp_state[i], 4);
  }
}

void AES::AddRoundKey(unsigned char **state, const unsigned char *key) {
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      state[i][j] = state[i][j] ^ key[i + 4 * j];
    }
  }
}

void AES::SubWord(unsigned char *a) {
  int i;
  for (i = 0; i < 4; i++) {
    a[i] = sbox[a[i] / 16][a[i] % 16];
  }
}

void AES::RotWord(unsigned char *a) {
  unsigned char c = a[0];
  a[0] = a[1];
  a[1] = a[2];
  a[2] = a[3];
  a[3] = c;
}

void AES::XorWords(const unsigned char *a, const unsigned char *b, unsigned char *c) {
  int i;
  for (i = 0; i < 4; i++) {
    c[i] = a[i] ^ b[i];
  }
}

void AES::Rcon(unsigned char *a, int n) {
  int i;
  unsigned char c = 1;
  for (i = 0; i < n - 1; i++) {
    c = xtime(c);
  }

  a[0] = c;
  a[1] = a[2] = a[3] = 0;
}

void AES::KeyExpansion(const unsigned char key[], unsigned char w[]) {
  auto temp = new unsigned char[4];
  auto rcon = new unsigned char[4];

  int i = 0;
  while (i < 4 * 8) {
    w[i] = key[i];
    i++;
  }

  i = 4 * 8;
  while (i < 4 * 4 * (14 + 1)) {
    temp[0] = w[i - 4 + 0];
    temp[1] = w[i - 4 + 1];
    temp[2] = w[i - 4 + 2];
    temp[3] = w[i - 4 + 3];

    if (i / 4 % 8 == 0) {
      RotWord(temp);
      SubWord(temp);
      Rcon(rcon, i / (8 * 4));
      XorWords(temp, rcon, temp);
    } else if (i / 4 % 8 == 4) {
      SubWord(temp);
    }

    w[i + 0] = w[i - 4 * 8] ^ temp[0];
    w[i + 1] = w[i + 1 - 4 * 8] ^ temp[1];
    w[i + 2] = w[i + 2 - 4 * 8] ^ temp[2];
    w[i + 3] = w[i + 3 - 4 * 8] ^ temp[3];
    i += 4;
  }

  delete[] rcon;
  delete[] temp;
}

void AES::XorBlocks(const unsigned char *a, const unsigned char *b, unsigned char *c, unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    c[i] = a[i] ^ b[i];
  }
}

std::vector<unsigned char> AES::ArrayToVector(unsigned char *a, unsigned int len) {
  return { a, a + len * sizeof(unsigned char)};
}

std::vector<unsigned char> AES::EncryptCFB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
  auto out = EncryptCFB(in.data(), (unsigned int)in.size(), key.data(), iv.data());
  std::vector<unsigned char> v = ArrayToVector(out, in.size());
  delete[] out;
  return v;
}

std::vector<unsigned char> AES::DecryptCFB(std::vector<unsigned char> in,
                                           std::vector<unsigned char> key,
                                           std::vector<unsigned char> iv) {
  auto out = DecryptCFB(in.data(), (unsigned int)in.size(), key.data(), iv.data());
  std::vector<unsigned char> v = ArrayToVector(out, (unsigned int)in.size());
  delete[] out;
  return v;
}
