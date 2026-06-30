#!/bin/bash

################################################################################
# LuxRegni Build Script
# Supports: Linux Native (ASCII Adventure), WASM Client, WASM Server
################################################################################

set -e  # Exit on error

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PROJECT_NAME="LuxRegni"
BUILD_DIR="build"
INSTALL_DIR="${PWD}/install"
JOBS=$(nproc)

# Emscripten configuration
EMSDK_PATH="${EMSDK_PATH:-/home/user/Lib/emsdk}"
EMSCRIPTEN_CMAKE="${EMSDK_PATH}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"

# Flags
BUILD_NATIVE=0
BUILD_WASM=0
BUILD_ASCII=0
BUILD_ALL=0
CLEAN_BUILD=0
VERBOSE=0

################################################################################
# Functions
################################################################################

print_header() {
    echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║${NC}  $1"
    echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
    echo ""
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

usage() {
    cat << EOF
${BLUE}Usage:${NC} $0 [OPTIONS]

${BLUE}Options:${NC}
    -n, --native        Build Linux native (ASCII Adventure)
    -w, --wasm          Build WASM targets (client + server)
    -a, --ascii         Build ASCII Adventure only
    -all, --all-targets Build all targets
    -c, --clean         Clean before building
    -v, --verbose       Verbose output
    -h, --help          Show this help message

${BLUE}Examples:${NC}
    # Build Linux native only
    $0 --native

    # Build all targets
    $0 --all-targets

    # Clean rebuild of ASCII Adventure
    $0 --ascii --clean

    # Build WASM with verbose output
    $0 --wasm --verbose

EOF
    exit 0
}

check_dependencies() {
    print_info "Checking dependencies..."
    
    local missing=0
    
    # Check CMake
    if ! command -v cmake &> /dev/null; then
        print_error "CMake not found. Install with: sudo apt install cmake"
        missing=1
    else
        local cmake_version=$(cmake --version | head -n1)
        print_success "$cmake_version"
    fi
    
    # Check C++ compiler
    if ! command -v g++ &> /dev/null; then
        print_error "G++ not found. Install with: sudo apt install build-essential"
        missing=1
    else
        print_success "$(g++ --version | head -n1)"
    fi
    
    # Check pkg-config
    if ! command -v pkg-config &> /dev/null; then
        print_warning "pkg-config not found (needed for Libtcod)"
    fi
    
    if [ $missing -eq 1 ]; then
        return 1
    fi
    
    return 0
}

check_emsdk() {
    if [ ! -f "$EMSCRIPTEN_CMAKE" ]; then
        print_error "Emscripten not found at: $EMSDK_PATH"
        print_info "Set EMSDK_PATH environment variable or edit this script"
        return 1
    fi
    
    print_success "Emscripten found at: $EMSDK_PATH"
    return 0
}

clean_build() {
    if [ -d "$BUILD_DIR" ]; then
        print_info "Cleaning previous builds..."
        rm -rf "$BUILD_DIR"
        print_success "Build directory cleaned"
    fi
}

build_native() {
    print_header "Building Linux Native (ASCII Adventure)"
    
    if ! check_dependencies; then
        print_error "Missing dependencies for native build"
        return 1
    fi
    
    local build_flags="-DCMAKE_BUILD_TYPE=Release"
    build_flags="$build_flags -DBUILD_ASCII_ADVENTURE=ON"
    build_flags="$build_flags -DBUILD_WASM_CLIENT=OFF"
    build_flags="$build_flags -DBUILD_WASM_SERVER=OFF"
    
    if [ $VERBOSE -eq 1 ]; then
        build_flags="$build_flags --debug-output"
    fi
    
    print_info "Configuring CMake..."
    if [ $CLEAN_BUILD -eq 1 ]; then
        clean_build
    fi
    
    mkdir -p "$BUILD_DIR"
    
    cmake -B "$BUILD_DIR" \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_ASCII_ADVENTURE=ON \
        -DBUILD_WASM_CLIENT=OFF \
        -DBUILD_WASM_SERVER=OFF \
        -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR"
    
    if [ $? -ne 0 ]; then
        print_error "CMake configuration failed"
        return 1
    fi
    
    print_info "Building..."
    cd "$BUILD_DIR"
    
    if [ $VERBOSE -eq 1 ]; then
        make -j$JOBS VERBOSE=1
    else
        make -j$JOBS
    fi
    
    if [ $? -ne 0 ]; then
        print_error "Build failed"
        cd ..
        return 1
    fi
    
    cd ..
    print_success "Linux native build completed"
    print_info "Binary: ${BUILD_DIR}/bin/ascii_adventure"
    
    return 0
}

build_wasm() {
    print_header "Building WASM Targets"
    
    if ! check_emsdk; then
        return 1
    fi
    
    # Source Emscripten environment
    print_info "Initializing Emscripten environment..."
    source "$EMSDK_PATH/emsdk_env.sh" || {
        print_error "Failed to source Emscripten environment"
        return 1
    }
    
    print_info "Emscripten version: $(emcc --version | head -n1)"
    
    if [ $CLEAN_BUILD -eq 1 ]; then
        clean_build
    fi
    
    mkdir -p "$BUILD_DIR"
    
    print_info "Configuring CMake for WASM..."
    emcmake cmake -B "$BUILD_DIR" \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE="$EMSCRIPTEN_CMAKE" \
        -DBUILD_ASCII_ADVENTURE=OFF \
        -DBUILD_WASM_CLIENT=ON \
        -DBUILD_WASM_SERVER=ON \
        -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR"
    
    if [ $? -ne 0 ]; then
        print_error "CMake configuration for WASM failed"
        return 1
    fi
    
    print_info "Building WASM..."
    cd "$BUILD_DIR"
    
    if [ $VERBOSE -eq 1 ]; then
        emmake make -j$JOBS VERBOSE=1
    else
        emmake make -j$JOBS
    fi
    
    if [ $? -ne 0 ]; then
        print_error "WASM build failed"
        cd ..
        return 1
    fi
    
    cd ..
    print_success "WASM build completed"
    print_info "Binaries:"
    print_info "  Client: ${BUILD_DIR}/bin/wasm_client.js"
    print_info "  Server: ${BUILD_DIR}/bin/wasm_server.js"
    
    return 0
}

build_ascii_only() {
    print_header "Building ASCII Adventure Only"
    build_native
}

build_all_targets() {
    print_header "Building All Targets"
    
    print_info "Building Linux native..."
    if ! build_native; then
        print_warning "Native build failed, continuing..."
    fi
    
    print_info "Building WASM targets..."
    if ! build_wasm; then
        print_warning "WASM build failed, continuing..."
    fi
    
    print_success "Build process completed"
}

install_artifacts() {
    print_info "Installing artifacts to: $INSTALL_DIR"
    
    mkdir -p "$INSTALL_DIR"
    
    if [ -f "${BUILD_DIR}/bin/ascii_adventure" ]; then
        cp "${BUILD_DIR}/bin/ascii_adventure" "$INSTALL_DIR/"
        print_success "Installed ascii_adventure"
    fi
    
    if [ -f "${BUILD_DIR}/bin/wasm_client.js" ]; then
        cp "${BUILD_DIR}/bin/wasm_client.js" "$INSTALL_DIR/"
        cp "${BUILD_DIR}/bin/wasm_client.wasm" "$INSTALL_DIR/" 2>/dev/null || true
        print_success "Installed WASM client"
    fi
    
    if [ -f "${BUILD_DIR}/bin/wasm_server.js" ]; then
        cp "${BUILD_DIR}/bin/wasm_server.js" "$INSTALL_DIR/"
        cp "${BUILD_DIR}/bin/wasm_server.wasm" "$INSTALL_DIR/" 2>/dev/null || true
        print_success "Installed WASM server"
    fi
}

print_build_summary() {
    print_header "Build Summary"
    
    echo "Project:      $PROJECT_NAME"
    echo "Build Dir:    $BUILD_DIR"
    echo "Install Dir:  $INSTALL_DIR"
    echo "Parallel Jobs: $JOBS"
    echo ""
    
    if [ -f "${BUILD_DIR}/bin/ascii_adventure" ]; then
        echo -e "${GREEN}✓ ASCII Adventure${NC} - Ready to run"
        echo "  Run: ${BUILD_DIR}/bin/ascii_adventure"
    fi
    
    if [ -f "${BUILD_DIR}/bin/wasm_client.js" ]; then
        echo -e "${GREEN}✓ WASM Client${NC} - Ready for web deployment"
    fi
    
    if [ -f "${BUILD_DIR}/bin/wasm_server.js" ]; then
        echo -e "${GREEN}✓ WASM Server${NC} - Ready for Node.js"
    fi
}

run_ascii_adventure() {
    if [ -f "${BUILD_DIR}/bin/ascii_adventure" ]; then
        print_info "Starting ASCII Adventure..."
        "${BUILD_DIR}/bin/ascii_adventure"
    else
        print_error "ascii_adventure binary not found. Build it first with: $0 --ascii"
    fi
}

################################################################################
# Main Script
################################################################################

main() {
    # Parse arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -n|--native)
                BUILD_NATIVE=1
                shift
                ;;
            -w|--wasm)
                BUILD_WASM=1
                shift
                ;;
            -a|--ascii)
                BUILD_ASCII=1
                shift
                ;;
            -all|--all-targets)
                BUILD_ALL=1
                shift
                ;;
            -c|--clean)
                CLEAN_BUILD=1
                shift
                ;;
            -v|--verbose)
                VERBOSE=1
                shift
                ;;
            -h|--help)
                usage
                ;;
            *)
                print_error "Unknown option: $1"
                usage
                ;;
        esac
    done
    
    # If no target specified, default to native
    if [ $BUILD_NATIVE -eq 0 ] && [ $BUILD_WASM -eq 0 ] && [ $BUILD_ASCII -eq 0 ] && [ $BUILD_ALL -eq 0 ]; then
        BUILD_NATIVE=1
    fi
    
    echo ""
    print_header "$PROJECT_NAME Build System"
    
    # Execute builds
    if [ $BUILD_ALL -eq 1 ]; then
        build_all_targets
    elif [ $BUILD_ASCII -eq 1 ]; then
        build_ascii_only
    else
        if [ $BUILD_NATIVE -eq 1 ]; then
            build_native || exit 1
        fi
        
        if [ $BUILD_WASM -eq 1 ]; then
            build_wasm || exit 1
        fi
    fi
    
    # Install and summarize
    install_artifacts
    print_build_summary
    
    echo ""
    print_success "Build completed successfully!"
}

# Run main
main "$@"
