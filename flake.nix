
{
  description = "A flake for building Path-Tracing_Renderer";
  inputs = {
    nixpkgs = {
      url = "nixpkgs/nixos-21.05";
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };

  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };
      path-tracing-renderer = (with pkgs; stdenv.mkDerivation {
          pname = "path-tracing-renderer";
          version = "0.0.1";
          src = ./.;
          nativeBuildInputs = [
            gcc
            glm
          ];
          buildPhase = "g++ -march=native -Ofast -s -std=c++11 -Wall -Wextra -Wshadow \"./src/image.cpp\" \"./src/rng.cpp\" \"./src/scene.cpp\" \"./src/trace.cpp\" \"./src/main.cpp\" -o \"./OpenPT\"";
          installPhase = ''
            mkdir -p $out/bin
            mv OpenPT $out/bin
          '';
        }
      );
    in rec {
      defaultApp = flake-utils.lib.mkApp {
        drv = defaultPackage;
      };
      defaultPackage = path-tracing-renderer;
      devShell = pkgs.mkShell {
        buildInputs = [
          path-tracing-renderer
        ];
      };
    }
  );
}
