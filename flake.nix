{
  description = "Advent of Code 2023";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    devshell = {
      url = "github:numtide/devshell";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = { self, nixpkgs, devshell, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; overlays = [ devshell.overlays.default ]; };
      in
      {
        devShells = rec {
          default = aoc2023;
          aoc2023 = pkgs.devshell.mkShell {
            imports = [ "${devshell}/extra/language/c.nix" ];
            name = "Advent of Code 2023";
            commands = [
              {
                name = "part1";
                category = "general commands";
                help = "Run $day's part 1";
                command = ''
                  ./prepare $1 1 && ./run $1 1 day$1/input
                '';
              }
              {
                name = "part2";
                category = "general commands";
                help = "Run $day's part 2";
                command = ''
                  ./prepare $1 2 && ./run $1 2 day$1/input
                '';
              }
            ];
          };
        };
      }
    );
}
