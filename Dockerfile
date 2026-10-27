# Optional environment provisioned by the user or harness before starting an agent (Linux x86-64).
# Native Linux with a Python virtual environment is the default. This image contains build tools, not the agent or game: mount your checkout, which holds
# orig/<GAMEID>/<GAMEID>, using tools/container.py (including linked-worktree Git paths).
#
#   docker build -t black-decomp .
#   python3 tools/container.py
#   (prepared shell)  python3 tools/setup.py
FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      ca-certificates git ninja-build python3 python3-pip python3-venv \
      binutils-mipsel-linux-gnu libc6-i386 xz-utils cpp \
 && rm -rf /var/lib/apt/lists/*

# Python packages (splat, spimdisasm, rabbitizer, m2c, ...), pinned in requirements.txt.
COPY requirements.txt /tmp/requirements.txt
RUN python3 -m venv /opt/venv && /opt/venv/bin/pip install --no-cache-dir -r /tmp/requirements.txt

# The pinned compilers, assemblers and wibo, verified by SHA-256 (see tools/toolchain.py).
COPY tools/toolchain.py tools/build/patch_ps2eeas.py /opt/black/tools/
COPY config/toolchain-local.json config/toolchain-compilers.json config/toolchain-assemblers.json /opt/black/config/
ENV BLACK_TOOLCHAIN_DIR=/opt/toolchain
RUN python3 /opt/black/tools/toolchain.py install --objdiff \
 && chmod -R a+rX /opt/toolchain

ENV PATH=/opt/venv/bin:$PATH
WORKDIR /workspace
CMD ["bash"]
