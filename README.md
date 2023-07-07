# STM32-AES

This project is an example of AES-128 implemented on an STM32L4R5ZI. This project has been optimized for code readability and learning purposes, hence it is not very efficient.

It allows you to encrypt and decrypt data in ECB and CBC modes using a 128 bit key.

# Usage

## Key Generation

To generate the necessary round keys for encryption and decryption, you can use the `GenerateKeys()` function. This functions takes a 128 bit key defined as an array of 16 bytes and a buffer to store the round keys in defined as a 2D array of 44 rows and 4 columns. An example of how to use this function is shown below:

```c
uint8_t key[16] = {0x00, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
uint8_t keys[44][4] = {0};
GenerateKeys(key, keys);
```

## Encryption

To encrypt a single block of 128 bits we first need to define our plaintext. This needs to be an array of 16 bytes. We can then call the `Encrypt()` function and it will return a pointer to the ciphertext. An example of how to use this function is shown below:

```c
char plaintext[16] = "Cool Plain Text!";
uint8_t* ciphertext = Encrypt((uint8_t*)plaintext, keys);
```

## Decryption

To decrypt a single block of 128 bits we can use the `Decrypt()` function. This function takes a pointer to the ciphertext and returns a pointer to the plaintext. An example of how to use this function is shown below:

```c
uint8_t* decryptedText = Decrypt(ciphertext, keys);
```

## CBC Mode Encryption

This implementation supports encrypting multiple blocks of data using the CBC (Cipher Block Chaining) mode. To encrypt we can use the `EncryptCBC()` function. This function takes a pointer to the plaintext, the length of the plaintext, an initialization vector as an array of 16 bytes, the round keys, and a buffer to store the ciphertext in. An example of how to use this function is shown below:

```c
uint8_t data[32] = "Hello World, This is my string!\0";
uint8_t IV[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };
uint8_t cipherRes[32] = {0};

// Encrypt
EncryptCBC(data, sizeof(data), IV, keys, cipherRes);
```

## CBC Mode Decryption

To decrypt using CBC mode we can simply use the `DecryptCBC()` function. This function takes a pointer to the ciphertext, the length of the ciphertext, an initialization vector as an array of 16 bytes, the round keys, and a buffer to store the plaintext in. An example of how to use this function is shown below:

```c
DecryptCBC(cipherRes, sizeof(cipherRes), IV, keys, plainCBC);
```

**N.B when using the CBC mode no padding is added so ensure that your input plaintext or ciphertext is a multiple of 16 bytes**