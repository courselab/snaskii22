{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  nativeBuildInputs = [
    ncurses5
  ];
  buildInputs = [
    gcc
    automake
    autoconf
    libtool
  ];
}
