{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gnumake
    pkgsCross.mingwW64.buildPackages.gcc
    wine64
  ];
}
