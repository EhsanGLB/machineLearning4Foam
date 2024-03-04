{
    fvScalarMatrix TEqn
    (
        fvm::ddt(rho*Cp, T)
      + rho*Cp*fvm::div(phi, T)
      - fvm::laplacian(kappa, T)
    );

    TEqn.relax();
    TEqn.solve();
}
