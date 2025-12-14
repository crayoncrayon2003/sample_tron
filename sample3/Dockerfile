# Dockerfile
FROM ubuntu:22.04

# 1. 必要なツールのインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-multilib \
    g++-multilib \
    git \
    nano \
    ca-certificates \
    libboost-all-dev \
    && rm -rf /var/lib/apt/lists/*

# 2. TOPPERS/ASP for Linux のクローン
WORKDIR /opt
RUN git clone https://github.com/morioka/toppers-asp-for-linux.git toppers

# 3. コンフィギュレータの修正とビルド
WORKDIR /opt/toppers/asp/cfg
RUN grep -rl "boost::next" . | xargs sed -i 's/boost::next/std::next/g' && \
    make depend && \
    make

# 4. 「asp-build」コマンドの作成
# 【修正点】並列ビルド(-j4)を廃止し、依存関係解決(depend)を追加して確実に実行する
RUN echo '#!/bin/bash' > /usr/local/bin/asp-build && \
    echo 'set -e' >> /usr/local/bin/asp-build && \
    echo 'BUILD_DIR="/tmp/asp_build"' >> /usr/local/bin/asp-build && \
    echo 'echo "Build Start..."' >> /usr/local/bin/asp-build && \
    echo 'mkdir -p $BUILD_DIR' >> /usr/local/bin/asp-build && \
    echo 'rm -rf $BUILD_DIR/*' >> /usr/local/bin/asp-build && \
    echo 'cd $BUILD_DIR' >> /usr/local/bin/asp-build && \
    echo '' >> /usr/local/bin/asp-build && \
    echo '# 1. Configureを実行してMakefileを生成' >> /usr/local/bin/asp-build && \
    echo '/opt/toppers/asp/configure -T linux_gcc > /dev/null' >> /usr/local/bin/asp-build && \
    echo '' >> /usr/local/bin/asp-build && \
    echo '# 2. ユーザーのソースコードをコピー' >> /usr/local/bin/asp-build && \
    echo 'cp -f /work/*.c .' >> /usr/local/bin/asp-build && \
    echo 'cp -f /work/*.h .' >> /usr/local/bin/asp-build && \
    echo 'cp -f /work/*.cfg .' >> /usr/local/bin/asp-build && \
    echo '' >> /usr/local/bin/asp-build && \
    echo '# 3. 依存関係を解決してからビルド実行 (直列)' >> /usr/local/bin/asp-build && \
    echo 'make depend' >> /usr/local/bin/asp-build && \
    echo 'make' >> /usr/local/bin/asp-build && \
    echo '' >> /usr/local/bin/asp-build && \
    echo 'if [ -f asp ]; then' >> /usr/local/bin/asp-build && \
    echo '  cp asp /work/asp.exe' >> /usr/local/bin/asp-build && \
    echo '  echo "========================================="' >> /usr/local/bin/asp-build && \
    echo '  echo "SUCCESS! Executable: ./asp.exe"' >> /usr/local/bin/asp-build && \
    echo '  echo "========================================="' >> /usr/local/bin/asp-build && \
    echo 'else' >> /usr/local/bin/asp-build && \
    echo '  echo "Build failed."' >> /usr/local/bin/asp-build && \
    echo '  exit 1' >> /usr/local/bin/asp-build && \
    echo 'fi' >> /usr/local/bin/asp-build && \
    chmod +x /usr/local/bin/asp-build

# 作業ディレクトリ設定
WORKDIR /work
CMD ["/bin/bash"]