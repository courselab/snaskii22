{ pkgs ? import <nixpkgs> {} }:


pkgs.mkShell {

  buildInputs = with pkgs; [
    ncurses
    gcc
    automake
    autoconf
    libtool
  ];

}
