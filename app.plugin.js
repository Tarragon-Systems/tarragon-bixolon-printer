const {
  withXcodeProject,
  withInfoPlist,
  withDangerousMod,
} = require("expo/config-plugins");
const path = require("path");
const fs = require("fs");

function withBixolonPrinter(config) {
  config = withInfoPlist(config, (config) => {
    config.modResults["UISupportedExternalAccessoryProtocols"] = [
      "com.bixolon.protocol",
    ];
    return config;
  });

  config = withXcodeProject(config, (config) => {
    const project = config.modResults;
    const target = project.getFirstTarget();

    // Copy xcframework to ios build directory
    const xcframeworkSrc = path.resolve(
      __dirname,
      "ios",
      "frmLabelPrinterSDK.xcframework"
    );
    const xcframeworkDest = path.join(
      config.modRequest.platformProjectRoot,
      "frmLabelPrinterSDK.xcframework"
    );
    if (!fs.existsSync(xcframeworkDest)) {
      fs.cpSync(xcframeworkSrc, xcframeworkDest, { recursive: true });
    }

    // Add the xcframework file reference
    const frameworkFileRef = project.generateUuid();
    project.hash.project.objects["PBXFileReference"] =
      project.hash.project.objects["PBXFileReference"] || {};
    project.hash.project.objects["PBXFileReference"][frameworkFileRef] = {
      isa: "PBXFileReference",
      lastKnownFileType: "wrapper.xcframework",
      name: "frmLabelPrinterSDK.xcframework",
      path: "frmLabelPrinterSDK.xcframework",
      sourceTree: '"<group>"',
    };
    project.hash.project.objects["PBXFileReference"][
      `${frameworkFileRef}_comment`
    ] = "frmLabelPrinterSDK.xcframework";

    // Add to Frameworks group
    const frameworksGroup = project.pbxGroupByName("Frameworks");
    if (frameworksGroup) {
      frameworksGroup.children.push({
        value: frameworkFileRef,
        comment: "frmLabelPrinterSDK.xcframework",
      });
    }

    // Create PBXBuildFile for linking
    const linkBuildFileUuid = project.generateUuid();
    project.hash.project.objects["PBXBuildFile"] =
      project.hash.project.objects["PBXBuildFile"] || {};
    project.hash.project.objects["PBXBuildFile"][linkBuildFileUuid] = {
      isa: "PBXBuildFile",
      fileRef: frameworkFileRef,
      fileRef_comment: "frmLabelPrinterSDK.xcframework",
    };
    project.hash.project.objects["PBXBuildFile"][
      `${linkBuildFileUuid}_comment`
    ] = "frmLabelPrinterSDK.xcframework in Frameworks";

    // Add to Frameworks build phase
    const frameworksBuildPhase = project.pbxFrameworksBuildPhaseObj(
      target.uuid
    );
    if (frameworksBuildPhase) {
      frameworksBuildPhase.files.push({
        value: linkBuildFileUuid,
        comment: "frmLabelPrinterSDK.xcframework in Frameworks",
      });
    }

    // Create PBXBuildFile for embedding
    const embedBuildFileUuid = project.generateUuid();
    project.hash.project.objects["PBXBuildFile"][embedBuildFileUuid] = {
      isa: "PBXBuildFile",
      fileRef: frameworkFileRef,
      fileRef_comment: "frmLabelPrinterSDK.xcframework",
      settings: { ATTRIBUTES: ["CodeSignOnCopy", "RemoveHeadersOnCopy"] },
    };
    project.hash.project.objects["PBXBuildFile"][
      `${embedBuildFileUuid}_comment`
    ] = "frmLabelPrinterSDK.xcframework in Embed Frameworks";

    // Create Embed Frameworks copy files build phase
    const embedPhaseUuid = project.generateUuid();
    project.hash.project.objects["PBXCopyFilesBuildPhase"] =
      project.hash.project.objects["PBXCopyFilesBuildPhase"] || {};
    project.hash.project.objects["PBXCopyFilesBuildPhase"][embedPhaseUuid] = {
      isa: "PBXCopyFilesBuildPhase",
      buildActionMask: 2147483647,
      dstPath: '""',
      dstSubfolderSpec: 10,
      files: [
        {
          value: embedBuildFileUuid,
          comment: "frmLabelPrinterSDK.xcframework in Embed Frameworks",
        },
      ],
      name: '"Embed Frameworks"',
      runOnlyForDeploymentPostprocessing: 0,
    };
    project.hash.project.objects["PBXCopyFilesBuildPhase"][
      `${embedPhaseUuid}_comment`
    ] = "Embed Frameworks";

    // Add embed phase to target's buildPhases
    const nativeTarget =
      project.hash.project.objects["PBXNativeTarget"][target.uuid];
    if (nativeTarget) {
      nativeTarget.buildPhases.push({
        value: embedPhaseUuid,
        comment: "Embed Frameworks",
      });
    }

    // Add system frameworks
    project.addFramework("ExternalAccessory.framework", { link: true });
    project.addFramework("CoreBluetooth.framework", { link: true });

    // Copy native module source files
    const nativeModuleSrc = path.resolve(
      __dirname,
      "ios",
      "BixolonPrinterModule.m"
    );
    const nativeModuleDest = path.join(
      config.modRequest.platformProjectRoot,
      config.modRequest.projectName,
      "BixolonPrinterModule.m"
    );
    const bridgingHeaderSrc = path.resolve(
      __dirname,
      "ios",
      "BixolonBridging.h"
    );
    const bridgingHeaderDest = path.join(
      config.modRequest.platformProjectRoot,
      config.modRequest.projectName,
      "BixolonBridging.h"
    );

    if (fs.existsSync(nativeModuleSrc)) {
      fs.copyFileSync(nativeModuleSrc, nativeModuleDest);
    }
    if (fs.existsSync(bridgingHeaderSrc)) {
      fs.copyFileSync(bridgingHeaderSrc, bridgingHeaderDest);
    }

    // Add .m file to Xcode project
    const mainGroupId = project.getFirstProject().firstProject.mainGroup;
    project.addSourceFile(
      `${config.modRequest.projectName}/BixolonPrinterModule.m`,
      { target: target.uuid },
      mainGroupId
    );

    // Add framework search paths
    const buildConfigs = project.pbxXCBuildConfigurationSection();
    for (const key in buildConfigs) {
      const bc = buildConfigs[key];
      if (bc.buildSettings) {
        const searchPaths = bc.buildSettings.FRAMEWORK_SEARCH_PATHS || [
          '"$(inherited)"',
        ];
        if (Array.isArray(searchPaths)) {
          if (!searchPaths.includes('"$(PROJECT_DIR)"')) {
            searchPaths.push('"$(PROJECT_DIR)"');
          }
        }
        bc.buildSettings.FRAMEWORK_SEARCH_PATHS = searchPaths;
      }
    }

    return config;
  });

  return config;
}

module.exports = withBixolonPrinter;
