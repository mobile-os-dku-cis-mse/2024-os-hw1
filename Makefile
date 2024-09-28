# Makefile

BUILD_DIR = build

# 리눅스 시스템 패키지 관리자에서 libyaml 설치 (예: Ubuntu의 경우)
install_deps:
	@which yaml > /dev/null 2>&1 || sudo apt-get install -y libyaml-dev

# 기본 타겟: libyaml을 설치하고 빌드
all: install_deps $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR)

# CMake 호출
$(BUILD_DIR)/Makefile:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

# Clean 타겟
clean:
	rm -rf $(BUILD_DIR)