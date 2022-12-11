{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-22.05";
  };

  outputs = { self, nixpkgs, ... }:

  let
    inherit (nixpkgs) lib;
    pkgsFor = nixpkgs.legacyPackages;
    genSystems = lib.genAttrs [
      "x86_64-linux"
    ];
  in rec {
    overlays.default = final: prev: rec {
      snaskii = prev.callPackage ./nix/default.nix { };
    };


    # nix develop
    devShells = genSystems (system:
    let
      pkgs = self.packages.${system};
    in {
      default = pkgsFor.${system}.callPackage ./nix/shell.nix { };
    });

    # nix build, nix shell, nix run
    packages = genSystems (system:
    let
      pkgs = import nixpkgs {
        inherit system;
        overlays = [ overlays.default ];
      };
    in {
      inherit (pkgs) snaskii;
      default = pkgs.snaskii;
    });



  };
}
