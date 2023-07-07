#ifndef AES_TESTS
#define AES_TESTS

void TestEncryptConstantKey(uint8_t key[16]);
void TestDecryptConstantKey();
void TestEncryptVariableKey();
void TestDecryptVariableKey();
void SpeedTest1MB();

#endif
