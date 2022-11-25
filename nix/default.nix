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

  installPhase = ''
    mkdir -p $out/bin
    chmod -R u+x $out

    cp src/snaskii $out/bin
    cp src/snaskii.bin $out/bin
    cp -r scenes $out
    chmod -R u+x $out/bin

  '';

}
