function showContentsMenuImage(relativePath) {
    document.write("<style>");
    document.write("    img.contentsMenu {");
    document.write("        position: fixed;");
    document.write("        right: 3px;");
    document.write("    }");
    document.write("</style>");

    document.write("<img class=\"contentsMenu\" src=\""+relativePath+"/../res/pics/oxygen/actions/help-about.png\" width=24 height=24 alt=\"Contents\">");
}

function copyright() {
    var date = new Date();

    document.write("Copyright ©2011-"+date.getFullYear());
}

// Note: for some very weird reasons, any file which is to be used to generate
//       a Qt help must be at least 512 bytes big, so...

// ############################################################################
// ###                                                                     ####
// ###   Just to make up for the fact that we need at least 512 bytes...   ####
// ###                                                                     ####
// ############################################################################
