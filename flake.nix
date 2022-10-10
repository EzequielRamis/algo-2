{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            clang
            clang-tools
            cmake
            libcxx
            bear
            gdb
            ninja
            (texlive.combine {
              inherit (pkgs.texlive)
                scheme-medium geometry babel fancyhdr lastpage framed todonotes
                hyperref amsmath xargs changepage;
            })
            texlab
          ];
        };
      });
}
