FROM ubuntu:focal

RUN apt-get update \
    && apt-get install -y software-properties-common \
    && add-apt-repository ppa:git-core/ppa \
    && add-apt-repository ppa:jonathonf/vim \
    && add-apt-repository ppa:fish-shell/release-3 \
    && add-apt-repository ppa:ubuntu-toolchain-r/test \
    && apt-get install -y \
        sudo \
        git \
        fish \
        vim \
        gdb \
        g++ \
        python3-pip \
        python3 \
        make \
        gcc-13 \
    && pip3 install conan black clang-format cmake-format cmake

ARG USERNAME=dannie
ARG USER_UID=1000
ARG USER_GID=1000

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -s /usr/bin/fish \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
