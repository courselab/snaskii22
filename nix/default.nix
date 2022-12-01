{ stdenv, gcc, automake, autoconf, libtool, ncurses5 }:

stdenv.mkDerivation rec {
  pname = "snaskii";
  version = "2.0.0";

  src = ../.;

  nativeBuildInputs = [
    gcc
    automake
    libtool
    autoconf
  ];
  buildInputs = [
    ncurses5
  ];

  preConfigure = ''
    touch NEWS README AUTHORS ChangeLog
    autoreconf --install
  '';

}
