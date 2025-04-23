#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/pqc_define.h"
#include "../include/pqc_extern.h"

// 테스트 결과 출력 매크로
#define TEST_SUCCESS(msg) printf("✓ %s: 성공\n", msg)
#define TEST_FAILURE(msg) printf("✗ %s: 실패\n", msg)

// ML-KEM-512 테스트
int test_mlkem512() {
    printf("\n === ML-KEM-512 테스트 ===\n");
    int success = 1;

    // 키 쌍 생성 테스트
    uint8_t pk[MLKEM512_PUBLIC_KEY_BYTES] = {0};
    uint8_t sk[MLKEM512_SECRET_KEY_BYTES] = {0};

    if (Kem_Keypair(pk, sk, ALG_MLKEM512) != OK) {
        TEST_FAILURE("ML-KEM-512 키 쌍 생성");
    }
    else {
        TEST_SUCCESS("ML-KEM-512 키 쌍 생성");
    }

    // 키 캡슐화 테스트
    uint8_t ct[MLKEM512_CIPHERTEXT_BYTES] = {0};
    uint8_t ss_enc[MLKEM512_SHARED_SECRET_BYTES] = {0};

    if (Kem_Encapsulate(ct, ss_enc, pk, ALG_MLKEM512) != OK) {
        TEST_FAILURE("ML-KEM-512 키 캡슐화");
        success = 0;
    }
    else {
        TEST_SUCCESS("ML-KEM-512 키 캡슐화");
    }

    // 키 디캡슐화 테스트
    uint8_t ss_dec[MLKEM512_SHARED_SECRET_BYTES] = {0};

    if (Kem_Decapsulate(ss_dec, ct, sk, ALG_MLKEM512) != OK) {
        TEST_FAILURE("ML-KEM-512 키 디캡슐화");
        success = 0;
    }
    else {
        TEST_SUCCESS("ML-KEM-512 키 디캡슐화");
    }

    // 공유 비밀 비교 테스트
    if (memcmp(ss_enc, ss_dec, MLKEM512_SHARED_SECRET_BYTES) != 0) {
        TEST_FAILURE("ML-KEM-512 공유 비밀 검증");
        success = 0;
    }
    else {
        TEST_SUCCESS("ML-KEM-512 공유 비밀 검증");
    }

    printf("=== ML-KEM-512 테스트 %s ===\n", success ? "성공" : "실패");
    return success;
}

// ML-KEM-768 테스트


// ML-DSA-44 테스트
int test_mldsa44() {
    printf("\n === ML-DSA-44 테스트 ===\n");
    int success = 1;

    // 키 쌍 생성 테스트
    uint8_t pk[MLDSA44_PUBLIC_KEY_BYTES] = {0};
    uint8_t sk[MLDSA44_SECRET_KEY_BYTES] = {0};

    if (Sign_Keypair(pk, sk, ALG_MLDSA44) != OK) {
        TEST_FAILURE("ML-DSA-44 키 쌍 생성");
        success = 0;
    }
    else {
        TEST_SUCCESS("ML-DSA-44 키 쌍 생성");
    }

    // 메시지 서명 테스트
    const char *message = "테스트 메시지.";
    uint8_t sig[MLDSA44_SIGNATURE_BYTES] = {0};
    size_t sig_len = 0;

    if (Sign_Signature(sig, &sig_len, (uint8_t *)message, strlen(message), sk, ALG_MLDSA44) != OK) {
        TEST_FAILURE("ML-DSA-44 서명 생성");
        success = 0;
    }
    else {
        TEST_SUCCESS("ML-DSA-44 서명 생성");
    }

    // 서명 검증 테스트
    if (Sign_Verify(sig, sig_len, (uint8_t *)message, strlen(message), pk, ALG_MLDSA44) != OK) {
        TEST_FAILURE("ML-DSA-44 서명 검증");
        success = 0;
    }
    else {
        TEST_SUCCESS("ML-DSA-44 서명 검증");
    }


    // 메시지 변조 테스트
    const char *tampered_message = "변조된 메시지입니다. 이 메시지는 ML-DSA-44로 서명됩니다.";
    if (Sign_Verify(sig, sig_len, (uint8_t*)tampered_message, strlen(tampered_message), pk, ALG_MLDSA44) == OK) {
        TEST_FAILURE("ML-DSA-44 변조 메시지 감지");
        success = 0;
    } else {
        TEST_SUCCESS("ML-DSA-44 변조 메시지 감지");
    }
    
    printf("=== ML-DSA-44 테스트 %s ===\n", success ? "성공" : "실패");
    return success;

}

// 메인 테스트 함수
int main() {
    printf("=== PQC API 테스트 시작 ===\n");

    int success = 1;

    // ML-KEM 테스트
    success &= test_mlkem512();

    // ML-DSA 테스트
    success &= test_mldsa44();

    printf("\n === ML-KEM PQC API 테스트 %s ===\n", success ? "성공" : "실패");
    
    return success ? 0 : 1;
}