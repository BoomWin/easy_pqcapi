CC = gcc
CFLAGS = -Wall -Wextra -O3
LDFLAGS = 

SRC_DIR = ..
INCLUDE_DIR = ../include
KEM_DIR = ../crypto_kem
SIGN_DIR = ../crypto_sign
COMMON_DIR = ../common

# 포함 디렉토리

INCLUDES = -I$(INCLUDE_DIR) \
           -I$(KEM_DIR)/ml-kem-512 -I$(KEM_DIR)/ml-kem-768 -I$(KEM_DIR)/ml-kem-1024 \
           -I$(SIGN_DIR)/ml-dsa-44 -I$(SIGN_DIR)/ml-dsa-65 -I$(SIGN_DIR)/ml-dsa-87 \
           -I$(COMMON_DIR)
# PQC API 소스 파일
PQCAPI_SRC = $(SRC_DIR)/src/pqcapi.c

# ML-KEM 소스 파일
KEM_512_SRC = $(wildcard $(KEM_DIR)/ml-kem-512/*.c)
KEM_768_SRC = $(wildcard $(KEM_DIR)/ml-kem-768/*.c)
KEM_1024_SRC = $(wildcard $(KEM_DIR)/ml-kem-1024/*.c)

# ML-DSA 소스 파일
DSA_44_SRC = $(wildcard $(SIGN_DIR)/ml-dsa-44/*.c)
DSA_65_SRC = $(wildcard $(SIGN_DIR)/ml-dsa-65/*.c)
DSA_87_SRC = $(wildcard $(SIGN_DIR)/ml-dsa-87/*.c)

# 공통 소스 파일
COMMON_SRC = $(wildcard $(COMMON_DIR)/*.c)
#  $(wildcard $(COMMON_DIR)/keccak2x/*.c) $(wildcard $(COMMON_DIR)/keccak4x/*.c)

# 테스트 소스 파일
TEST_SRC = test_pqcapi.c

# 소스 파일 통합
ALL_SRC = $(PQCAPI_SRC) $(KEM_512_SRC) $(KEM_768_SRC) $(KEM_1024_SRC) $(DSA_44_SRC) $(DSA_65_SRC) $(DSA_87_SRC) $(COMMON_SRC)


# 목적 파일
OBJS = $(ALL_SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# 테스트 실행 파일
TEST_EXEC = test_pqcapi

# 기본 타겟
all: $(TEST_EXEC)

# 테스트 실행 파일 빌드
$(TEST_EXEC): $(TEST_OBJ) $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^


# 테스트 소스 컴파일
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 테스트 실행
run: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(TEST_OBJ) $(TEST_EXEC)

.PHONY: all run clean