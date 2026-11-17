{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gnumake
    pkg-config
    pkgsCross.mingwW64.buildPackages.gcc
  ];

  buildInputs = with pkgs; [
    libGL
    xorg.xorgproto
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXi
  ];
}
