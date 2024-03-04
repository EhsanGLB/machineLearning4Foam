{
    volScalarField kappaEff
    (
        "kappaEff",
        (turbulence->nut()/Prt)*rho*Cp + kappa
    );

    fvScalarMatrix TEqn
    (
        rho*Cp*fvm::div(phi, T)
      + rho*Cp*fvm::SuSp(-fvc::div(phi), T)
      - fvm::laplacian(kappaEff, T)
    );

    TEqn.relax();
    TEqn.solve();
}
