{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gnumake
    pkgsCross.mingwW64.buildPackages.gcc
    wineWowPackages.stable # Optional: lets you run `wine build/app.exe` on NixOS
  ];
}
