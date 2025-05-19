#include "../include/pqc_define.h"
#include "../include/pqc_extern.h"
#include "../include/pqc_return.h"  // 새로 추가된 헤더
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_mlkem512() {
    uint8_t pk[MLKEM512_PUBLIC_KEY_BYTES];
    uint8_t sk[MLKEM512_SECRET_KEY_BYTES];
    uint8_t ct[MLKEM512_CIPHERTEXT_BYTES];
    uint8_t ss1[MLKEM512_SHARED_SECRET_BYTES];
    uint8_t ss2[MLKEM512_SHARED_SECRET_BYTES];
    int result;
    
    printf("ML-KEM-512 테스트 시작...\n");
    
    // 키페어 생성 테스트
    result = Kem_Keypair(pk, sk, ALG_MLKEM512);
    if (result != ML_KEM_512_KEYPAIR_SUCCESS) {
        printf("ML-KEM-512 키페어 생성 실패: 0x%08x\n", result);
        exit(1);
    }

    printf("ML-KEM-512 키페어 생성 성공\n");
    
    // 캡슐화 테스트
    result = Kem_Encapsulate(ct, ss1, pk, ALG_MLKEM512);
    if (result != ML_KEM_512_ENCAP_SUCCESS) {
        printf("ML-KEM-512 캡슐화 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-KEM-512 캡슐화 성공\n");
    
    // 디캡슐화 테스트
    result = Kem_Decapsulate(ss2, ct, sk, ALG_MLKEM512);
    if (result != ML_KEM_512_DECAP_SUCCESS) {
        printf("ML-KEM-512 디캡슐화 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-KEM-512 디캡슐화 성공\n");
    
    // 결과 비교
    if (memcmp(ss1, ss2, MLKEM512_SHARED_SECRET_BYTES) != 0) {
        printf("ML-KEM-512 공유 비밀 불일치!\n");
        exit(1);
    }
    
    printf("ML-KEM-512 테스트 성공: 공유 비밀 일치 확인됨\n");
}

void test_mlkem768() {
    uint8_t pk[MLKEM768_PUBLIC_KEY_BYTES];
    uint8_t sk[MLKEM768_SECRET_KEY_BYTES];
    uint8_t ct[MLKEM768_CIPHERTEXT_BYTES];
    uint8_t ss1[MLKEM768_SHARED_SECRET_BYTES];
    uint8_t ss2[MLKEM768_SHARED_SECRET_BYTES];
    int result;
    
    printf("ML-KEM-768 테스트 시작...\n");
    
    // 키페어 생성 테스트
    result = Kem_Keypair(pk, sk, ALG_MLKEM768);
    if (result != ML_KEM_768_KEYPAIR_SUCCESS) {
        printf("ML-KEM-768 키페어 생성 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-KEM-768 키페어 생성 성공\n");
    
    // 캡슐화 테스트
    result = Kem_Encapsulate(ct, ss1, pk, ALG_MLKEM768);
    if (result != ML_KEM_768_ENCAP_SUCCESS) {
        printf("ML-KEM-768 캡슐화 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-KEM-768 캡슐화 성공\n");
    
    // 디캡슐화 테스트
    result = Kem_Decapsulate(ss2, ct, sk, ALG_MLKEM768);
    if (result != ML_KEM_768_DECAP_SUCCESS) {
        printf("ML-KEM-768 디캡슐화 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-KEM-768 디캡슐화 성공\n");
    
    // 결과 비교
    if (memcmp(ss1, ss2, MLKEM768_SHARED_SECRET_BYTES) != 0) {
        printf("ML-KEM-768 공유 비밀 불일치!\n");
        exit(1);
    }
    
    printf("ML-KEM-768 테스트 성공: 공유 비밀 일치 확인됨\n");
}

// ML-KEM-1024 테스트도 유사하게 구현 가능

// ML-DSA 테스트 코드 예시
void test_mldsa44() {
    uint8_t pk[MLDSA44_PUBLIC_KEY_BYTES];
    uint8_t sk[MLDSA44_SECRET_KEY_BYTES];
    uint8_t sig[MLDSA44_SIGNATURE_BYTES];
    size_t siglen;
    uint8_t message[] = "테스트 메시지입니다.";
    size_t msglen = sizeof(message) - 1; // NULL 문자 제외
    int result;
    
    printf("ML-DSA-44 테스트 시작...\n");
    
    // 키페어 생성 테스트
    result = Sign_Keypair(pk, sk, ALG_MLDSA44);
    if (result != ML_DSA_44_KEYPAIR_SUCCESS) {
        printf("ML-DSA-44 키페어 생성 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-DSA-44 키페어 생성 성공\n");
    
    // 서명 생성 테스트
    result = Sign_Signature(sig, &siglen, message, msglen, sk, ALG_MLDSA44);
    if (result != ML_DSA_44_SIGN_SUCCESS) {
        printf("ML-DSA-44 서명 생성 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-DSA-44 서명 생성 성공 (서명 길이: %zu)\n", siglen);
    
    // 서명 검증 테스트
    result = Sign_Verify(sig, siglen, message, msglen, pk, ALG_MLDSA44);
    if (result != ML_DSA_44_VERIFY_SUCCESS) {
        printf("ML-DSA-44 서명 검증 실패: 0x%08x\n", result);
        exit(1);
    }
    printf("ML-DSA-44 서명 검증 성공\n");
    
    // 메시지 변조 검증 테스트
    if (msglen > 0) {
        uint8_t modified_message[sizeof(message)];
        memcpy(modified_message, message, msglen);
        modified_message[0] ^= 0x01; // 첫 바이트 변조
        
        result = Sign_Verify(sig, siglen, modified_message, msglen, pk, ALG_MLDSA44);
        if (result == ML_DSA_44_VERIFY_SUCCESS) {
            printf("ML-DSA-44 오류: 변조된 메시지가 검증을 통과했습니다!\n");
            exit(1);
        }
        printf("ML-DSA-44 변조 감지 테스트 성공\n");
    }
    
    printf("ML-DSA-44 테스트 완료: 모든 테스트 통과\n");
}

// 오류 테스트 예시: 잘못된 알고리즘 번호 테스트
void test_error_handling() {
    uint8_t pk[MLKEM512_PUBLIC_KEY_BYTES];
    uint8_t sk[MLKEM512_SECRET_KEY_BYTES];
    int result;
    
    printf("오류 처리 테스트 시작...\n");
    
    // 잘못된 알고리즘 번호 테스트
    unsigned int invalid_alg = 99; // 유효하지 않은 알고리즘 번호
    result = Kem_Keypair(pk, sk, invalid_alg);
    if (result != PQC_UNSUPPORTED_ALGORITHM) {
        printf("오류 처리 테스트 실패: 잘못된 알고리즘 번호가 감지되지 않음 (반환값: 0x%08x)\n", result);
        exit(1);
    }
    printf("오류 처리 테스트 성공: 잘못된 알고리즘 번호 감지됨\n");
    
    // NULL 포인터 테스트
    result = Kem_Keypair(NULL, sk, ALG_MLKEM512);
    if (result != PQC_NULL_POINTER_ERROR) {
        printf("오류 처리 테스트 실패: NULL 포인터가 감지되지 않음 (반환값: 0x%08x)\n", result);
        exit(1);
    }
    printf("오류 처리 테스트 성공: NULL 포인터 감지됨\n");
    
    printf("오류 처리 테스트 완료: 모든 테스트 통과\n");
}

int main() {
    printf("PQC API 라이브러리 테스트 시작\n");
    printf("==================================\n\n");
    
    // 각 알고리즘 테스트 실행
    test_mlkem512();
    printf("\n");
    
    test_mlkem768();
    printf("\n");
    
    // ML-KEM-1024 테스트 함수 호출 (구현 필요)
    // test_mlkem1024();
    // printf("\n");
    
    test_mldsa44();
    printf("\n");
    
    // ML-DSA-65, ML-DSA-87 테스트 함수 호출 (구현 필요)
    // test_mldsa65();
    // printf("\n");
    // test_mldsa87();
    // printf("\n");
    
    // 오류 처리 테스트
    test_error_handling();
    printf("\n");
    
    printf("==================================\n");
    printf("모든 테스트 성공적으로 완료\n");
    
    return 0;
}