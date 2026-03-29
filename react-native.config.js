module.exports = {
  dependency: {
    platforms: {
      android: {
        packageImportPath: 'import com.tarragon.bixolonprinter.BixolonPrinterPackage;',
        packageInstance: 'new BixolonPrinterPackage()',
      },
      ios: null, // iOS is handled via the config plugin
    },
  },
};
