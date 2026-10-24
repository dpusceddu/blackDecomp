# Reproducible build environment for the matching rebuild (Linux x86-64; on other hosts run it under
# `docker run --platform linux/amd64`). The image contains the tools, not the game: mount your checkout, which holds
# orig/<GAMEID>/<GAMEID>, at /workspace.
#
#   docker build -t black-decomp .
#   docker run --rm -it -v "$PWD":/workspace black-decomp
#   (inside)  python3 configure.py && ninja
FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      ca-certificates git ninja-build python3 python3-pip python3-venv \
      binutils-mipsel-linux-gnu libc6-i386 xz-utils \
 && rm -rf /var/lib/apt/lists/*

# Python packages (splat, spimdisasm, rabbitizer, m2c, ...), pinned in requirements.txt.
COPY requirements.txt /tmp/requirements.txt
RUN python3 -m venv /opt/venv && /opt/venv/bin/pip install --no-cache-dir -r /tmp/requirements.txt

# The pinned compilers, assemblers and wibo, verified by SHA-256 (see tools/toolchain.py).
COPY tools/toolchain.py tools/build/patch_ps2eeas.py /opt/black/tools/
COPY config/toolchain-local.json config/toolchain-compilers.json config/toolchain-assemblers.json /opt/black/config/
ENV BLACK_TOOLCHAIN_DIR=/opt/toolchain
RUN python3 /opt/black/tools/toolchain.py install

ENV PATH=/opt/venv/bin:$PATH
WORKDIR /workspace
CMD ["bash"]
