{ pkgs, lib, config, inputs, ... }:

{
  packages = with pkgs; [ 
     cmake
     git
     pkg-config
     mesa
     libglvnd
     ] ++ lib.optionals stdenv.isLinux [
     egl-wayland
     wayland
     waylandpp
     libffi
     libxkbcommon

     xorg.libX11
     xorg.libXcursor
     xorg.libXi
     xorg.libXrandr
     xorg.libXinerama
  ];

  tasks = {
     "breakout:build".exec = ''cmake -B build && cmake --build build'';
     "breakout:test".exec = ''./build/breakout'';  
#   "devenv:enterShell".after = [ "myproj:setup" ];
  };
  enterShell = ''
  '';

  env.LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [ pkgs.wayland pkgs.libxkbcommon pkgs.egl-wayland pkgs.glfw pkgs.libffi ];

  # https://devenv.sh/tests/
  enterTest = ''
    echo "Running tests"
    git --version | grep --color=auto "${pkgs.git.version}"
  '';

  # https://devenv.sh/git-hooks/
  # git-hooks.hooks.shellcheck.enable = true;

  # See full reference at https://devenv.sh/reference/options/
}
