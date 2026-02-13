{ pkgs, lib, config, inputs, ... }:

{
  packages = with pkgs; [ 
     cmake
     libGLU
     zlib
     minizip
     wayland
     libxkbcommon
  ];

  tasks = {
     "build".exec = ''cmake -B build && cd build && make'';
  #   "devenv:enterShell".after = [ "myproj:setup" ];
  };

  # https://devenv.sh/tests/
  enterTest = ''
    echo "Running tests"
    git --version | grep --color=auto "${pkgs.git.version}"
  '';

  # https://devenv.sh/git-hooks/
  # git-hooks.hooks.shellcheck.enable = true;

  # See full reference at https://devenv.sh/reference/options/
}
