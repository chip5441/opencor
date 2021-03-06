var jsonData = { "versions": [
                   { "major": 0, "minor": 0, "patch": 0, "day": 14, "month": 2, "year": 2020, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 10",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".pkg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>Graph Panel widget:</strong> fixed a small problem that resulted in the legend being misplaced when exporting a graph panel (see issue <a href=\"https://github.com/opencor/opencor/issues/2297\">#2297</a>)." },
                       { "change": "<strong>CellML support:</strong> improved the generation of runtime (see issue <a href=\"https://github.com/opencor/opencor/issues/2285\">#2285</a>)." },
                       { "change": "<strong>CellML Text view:</strong> greatly reduced the time and memory required to do syntax highlighting (see issue <a href=\"https://github.com/opencor/opencor/issues/2284\">#2284</a>)." },
                       { "change": "<strong>Simulation support:</strong> fixed a small problem with not being able to reset a simulation that generates NANs (see issue <a href=\"https://github.com/opencor/opencor/issues/2299\">#2299</a>)." },
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 20, "month": 1, "year": 2020, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 10",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".pkg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> can now reload a file using <code>Ctrl</code>+<code>R</code> (see issue <a href=\"https://github.com/opencor/opencor/issues/2286\">#2286</a>)." },
                       { "change": "<strong>Simulation Experiment view:</strong> can now customise the font size of the different bits of text in a graph panel (see issue <a href=\"https://github.com/opencor/opencor/issues/2271\">#2271</a>). Fixed a small GUI glitch on macOS (see issue <a href=\"https://github.com/opencor/opencor/issues/2277\">#2277</a>). Fixed an issue with reloading a <a href=\"https://sed-ml.github.io/\">SED-ML</a> file / <a href=\"https://co.mbine.org/documents/archive\">COMBINE archive</a> potentially crashing OpenCOR (see issue <a href=\"https://github.com/opencor/opencor/issues/2290\">#2290</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://llvm.org/\">LLVM</a>+<a href=\"https://clang.llvm.org/\">Clang</a> to version 9.0.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/2269\">#2269</a>). Upgraded the <a href=\"https://computation.llnl.gov/projects/sundials\">SUNDIALS</a> library to version 5.1.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/2272\">#2272</a>). Upgraded <a href=\"https://libgit2.github.com/\">libgit2</a> to version 0.28.4 (see issue <a href=\"https://github.com/opencor/opencor/issues/2280\">#2280</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 19.3.2 (see issue <a href=\"https://github.com/opencor/opencor/issues/2281\">#2281</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 20, "month": 12, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> don't ask to confirm the overwriting of a file when on macOS 10.15 (see issue <a href=\"https://github.com/opencor/opencor/issues/2261\">#2261</a>). Fixed a couple of issues with our splash screen (see issue <a href=\"https://github.com/opencor/opencor/issues/2265\">#2265</a>)." },
                       { "change": "<strong>Graph Panel widget:</strong> prevent it from flickering when it is shown as disabled (see issue <a href=\"https://github.com/opencor/opencor/issues/2263\">#2263</a>)." },
                       { "change": "<strong>Simulation Experiment view:</strong> can now reopen a remote <a href=\"https://cellml.org/\">CellML</a> file from a <a href=\"https://sed-ml.github.io/\">SED-ML</a> file (see issue <a href=\"https://github.com/opencor/opencor/issues/2191\">#2191</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://github.com/qtwebkit/qtwebkit/wiki\">QtWebKit</a> to v5.212.0-alpha3 (see issue <a href=\"https://github.com/opencor/opencor/issues/2252\">#2252</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 13, "month": 12, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> Replaced our use of <a href=\"https://developer.apple.com/library/archive/documentation/DeveloperTools/Conceptual/PackageMakerUserGuide/Introduction/Introduction.html\">PackageMaker</a> with that of productbuild on <a href=\"https://en.wikipedia.org/wiki/MacOS\">macOS</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/2210\">#2210</a>). A selectable plugin cannot be needed by another plugin (see issue <a href=\"https://github.com/opencor/opencor/issues/2247\">#2247</a>)." },
                       { "change": "<strong>Python support:</strong> added (initial) support for <a href=\"https://python.org/\">Python</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/1255\">#1255</a>). Added some <a href=\"https://python.org/\">Python</a>-based tests (see issue <a href=\"https://github.com/opencor/opencor/issues/2178\">#2178</a>). Now update the environment variable <code>PATH</code> using <code>\\</code> rather than <code>/</code> on Windows (see issue <a href=\"https://github.com/opencor/opencor/issues/2219\">#2219</a>). Merged our duplicated code (see issue <a href=\"https://github.com/opencor/opencor/issues/2225\">#2225</a>). Don't make our JupyterKernel and PythonShell plugins selectable (see issue <a href=\"https://github.com/opencor/opencor/issues/2245\">#2245</a>). Make sure that \"implementation\" and \"implementation_version\" are properly set in the JupyterKernel plugin (see issue <a href=\"https://github.com/opencor/opencor/issues/2250\">#2250</a>)." },
                       { "change": "<strong>CellML support:</strong> fixed an issue with the CellML API wrongly allowing code generation for non-runnable models (see issue <a href=\"https://github.com/opencor/opencor/issues/2240\">#2240</a>)." },
                       { "change": "<strong>SED-ML support:</strong> added support left and right triangle symbols (see issue <a href=\"https://github.com/opencor/opencor/issues/2173\">#2173</a>)." },
                       { "change": "<strong>Simulation support:</strong> don't require all our solvers to be installed anymore (see issue <a href=\"https://github.com/opencor/opencor/issues/2234\">#2234</a>)." },
                       { "change": "<strong>Simulation Experiment view:</strong> properly handle the Graph Panel properties (see issue <a href=\"https://github.com/opencor/opencor/issues/2171\">#2171</a>). Make sure that curves are plotted with all of their original settings when reloading a <a href=\"https://sed-ml.github.io/\">SED-ML</a> file (see issue <a href=\"https://github.com/opencor/opencor/issues/2176\">#2176</a>). Make sure that all of a solver's properties get saved to a <a href=\"https://sed-ml.github.io/\">SED-ML</a> file (see issue <a href=\"https://github.com/opencor/opencor/issues/2185\">#2185</a>). Don't access our central widget directly anymore (see issue <a href=\"https://github.com/opencor/opencor/issues/2218\">#2218</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded the <a href=\"https://openssl.org/\">OpenSSL</a> library to version 1.1.1d (see issue <a href=\"https://github.com/opencor/opencor/issues/2157\">#2157</a>). Upgraded <a href=\"https://llvm.org/\">LLVM</a>+<a href=\"https://clang.llvm.org/\">Clang</a> to version 9.0.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/2161\">#2161</a>). Upgraded the <a href=\"https://computation.llnl.gov/projects/sundials\">SUNDIALS</a> library to version 5.0.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/2198\">#2198</a>). Upgraded <a href=\"https://riverbankcomputing.com/software/qscintilla/intro\">QScintilla</a> to version 2.11.3 (see issue <a href=\"https://github.com/opencor/opencor/issues/2208\">#2208</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 19.2.6 (see issue <a href=\"https://github.com/opencor/opencor/issues/2230\">#2230</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 9, "month": 9, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> prevent OpenCOR from crashing when on Windows, maximised and trying to open a dialog (see issue <a href=\"https://github.com/opencor/opencor/issues/2154\">#2154</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://llvm.org/\">LLVM</a>+<a href=\"https://clang.llvm.org/\">Clang</a> to version 8.0.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/2147\">#2147</a>). Upgraded <a href=\"https://libgit2.github.com/\">libgit2</a> to version 0.28.3 (see issue <a href=\"https://github.com/opencor/opencor/issues/2148\">#2148</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 19.1.5 (see issue <a href=\"https://github.com/opencor/opencor/issues/2149\">#2149</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 19, "month": 7, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> make sure that we have a view before trying to import a file using OpenCOR's <a href=\"https://en.wikipedia.org/wiki/Uniform_Resource_Identifier\">URI scheme</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/2140\">#2140</a>)." },
                       { "change": "<strong>Simulation support:</strong> improved the accuracy of algebraic variables that depend on the value of some state variables (see issue <a href=\"https://github.com/opencor/opencor/issues/2139\">#2139</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded the <a href=\"https://openssl.org/\">OpenSSL</a> library to version 1.1.1c (see issue <a href=\"https://github.com/opencor/opencor/issues/1801\">#1801</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 27, "month": 6, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> prebuilt third-party libraries are now installed under <a href=\"https://github.com/opencor/opencor/tree/master/ext\"><code>[OpenCOR]/ext</code></a> (see issue <a href=\"https://github.com/opencor/opencor/issues/2126\">#2126</a>)." },
                       { "change": "<strong>CellML Text view:</strong> can once again read a <a href=\"https://cellml.org/\">CellML</a> file that has no XML processing instruction (see issue <a href=\"https://github.com/opencor/opencor/issues/2125\">#2125</a>)." },
                       { "change": "<strong>Simulation Experiment view:</strong> properly disable the `Reset All Model Parameters` button (see issue <a href=\"https://github.com/opencor/opencor/issues/2116\">#2116</a>). Fixed an issue with the plotting of simulation data being potentially (very) choppy (see issue <a href=\"https://github.com/opencor/opencor/issues/2118\">#2118</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://jquery.com/\">jQuery</a> to version 3.4.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/2122\">#2122</a>). Upgraded <a href=\"https://libgit2.github.com/\">libgit2</a> to version 0.28.2 (see issue <a href=\"https://github.com/opencor/opencor/issues/2123\">#2123</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 19.1.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/2124\">#2124</a>). Upgraded <a href=\"https://riverbankcomputing.com/software/qscintilla/intro\">QScintilla</a> to version 2.11.2 (see issue <a href=\"https://github.com/opencor/opencor/issues/2131\">#2131</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 17, "month": 6, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> support <a href=\"https://en.wikipedia.org/wiki/Ubuntu_version_history#Ubuntu_19.04_(Disco_Dingo)\">Ubuntu 19.04</a> by shipping <a href=\"https://packages.ubuntu.com/bionic/libtinfo5\">libtinfo.so.5</a> on Linux (see issue <a href=\"https://github.com/opencor/opencor/issues/2075\">#2075</a>). now return the exit code of a <a href=\"https://en.wikipedia.org/wiki/Command-line_interface\">CLI</a> plugin command (see issue <a href=\"https://github.com/opencor/opencor/issues/2107\">#2107</a>)." },
                       { "change": "<strong>CellML support:</strong> improved the validation reporting of models with imports (see issue <a href=\"https://github.com/opencor/opencor/issues/2109\">#2109</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded the <a href=\"https://openssl.org/\">OpenSSL</a> library to version 1.0.2s (see issue <a href=\"https://github.com/opencor/opencor/issues/2105\">#2105</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 23, "month": 5, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> fixed an issue with <a href=\"https://qt.io/\">Qt</a> not being able to find its platform plugin anymore (see issue <a href=\"https://github.com/opencor/opencor/issues/2089\">#2089</a>)." },
                       { "change": "<strong>Simulation support:</strong> allow a remote <a href=\"https://sed-ml.github.io/\">SED-ML</a> file to be run headless (see issue <a href=\"https://github.com/opencor/opencor/issues/2085\">#2085</a>)." },
                       { "change": "<strong>Help window:</strong> fixed and issue with a blank page being shown rather than the documentation itself (see issue <a href=\"https://github.com/opencor/opencor/issues/2099\">#2099</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> fixed an issue with <a href=\"https://libgit2.github.com/\">libgit2</a> referencing two different copies of <a href=\"https://zlib.net/\">zlib</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/2088\">#2088</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 13, "month": 5, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>SED-ML support:</strong> fixed our detection of <a href=\"https://sed-ml.github.io/\">SED-ML</a> file (see issue <a href=\"https://github.com/opencor/opencor/issues/2082\">#2082</a>)." },
                       { "change": "<strong>Simulation support:</strong> generalised the reporting of a simulation's issues (see issue <a href=\"https://github.com/opencor/opencor/issues/2080\">#2080</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 5, "month": 5, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 18.04 LTS (Bionic Beaver) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> now rely on <a href=\"https://visualstudio.microsoft.com/downloads/\">Visual Studio 2017</a> to build OpenCOR on <a href=\"https://en.wikipedia.org/wiki/Microsoft_Windows\">Windows</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/2041\">#2041</a>). Upgraded our minimum requirement to <a href=\"https://en.wikipedia.org/wiki/Ubuntu_version_history#Ubuntu_18.04_LTS_(Bionic_Beaver)\">Ubuntu 18.04 LTS</a> on Linux (see issue <a href=\"https://github.com/opencor/opencor/issues/2050\">#2050</a>). Renamed QScintillaSupport to QScintillaWidget (see issue <a href=\"https://github.com/opencor/opencor/issues/2066\">#2066</a>)." },
                       { "change": "<strong>PMR Workspaces window:</strong> first list changed files and then show the user's comment (in the synchronisation dialog; see issue <a href=\"https://github.com/opencor/opencor/issues/2065\">#2065</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://llvm.org/\">LLVM</a>+<a href=\"https://clang.llvm.org/\">Clang</a> to version 8.0.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/2040\">#2040</a>). Upgraded <a href=\"https://github.com/fbergmann/libSEDML/\">libSEDML</a> to version 0.4.4 (see issue <a href=\"https://github.com/opencor/opencor/issues/2042\">#2042</a>). Upgraded <a href=\"http://sbml.org/Software/libSBML/\">libSBML</a> to version 5.18.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/2064\">#2064</a>). Upgraded <a href=\"https://jquery.com/\">jQuery</a> to version 3.4.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/2068\">#2068</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 19.0.2 (see issue <a href=\"https://github.com/opencor/opencor/issues/2070\">#2070</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 7, "month": 3, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 16.04 LTS (Xenial Xerus) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> enforce the use of Light Mode on <a href=\"https://en.wikipedia.org/wiki/MacOS\">macOS</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/1991\">#1991</a>). Added the <code>importFile</code> and <code>importFiles</code> commands to OpenCOR's <a href=\"https://en.wikipedia.org/wiki/Uniform_Resource_Identifier\">URI scheme</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/2000\">#2000</a>). OpenCOR's geometry is now properly restored on macOS when there is at least one remote file (see issue <a href=\"https://github.com/opencor/opencor/issues/2030\">#2030</a>)." },
                       { "change": "<strong>CSV data store:</strong> improved our detection of CSV files (see issue <a href=\"https://github.com/opencor/opencor/issues/2019\">#2019</a>)." },
                       { "change": "<strong>PMR Workspaces window:</strong> make sure that a folder is writable (see issue <a href=\"https://github.com/opencor/opencor/issues/2032\">#2032</a>)." },
                       { "change": "<strong>Simulation Experiment view:</strong> fixed an issue with a <a href=\"https://sed-ml.github.io/\">SED-ML</a> file / <a href=\"https://co.mbine.org/documents/archive\">COMBINE archive</a> being considered modified after changing languages (see issue <a href=\"https://github.com/opencor/opencor/issues/2001\">#2001</a>). Make some widgets look properly disabled when they are (see issue <a href=\"https://github.com/opencor/opencor/issues/2022\">#2022</a>). Properly handle the import of the same data in different files (see issue <a href=\"https://github.com/opencor/opencor/issues/2028\">#2028</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://riverbankcomputing.com/software/qscintilla/intro\">QScintilla</a> to version 2.11.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/1983\">#1983</a>). Upgraded <a href=\"https://libgit2.github.com/\">libgit2</a> to version 0.28.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/1993\">#1993</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 18.3.4 (see issue <a href=\"https://github.com/opencor/opencor/issues/1994\">#1994</a>). Upgraded the <a href=\"https://computation.llnl.gov/projects/sundials\">SUNDIALS</a> library to version 4.1.0 (see issue <a href=\"https://github.com/opencor/opencor/issues/1995\">#1995</a>). Upgraded the <a href=\"https://openssl.org/\">OpenSSL</a> library to version 1.0.2r (see issue <a href=\"https://github.com/opencor/opencor/issues/2009\">#2009</a>). Upgraded <a href=\"https://katex.org/\">KaTeX</a> to version 0.10.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/2014\">#2014</a>)." }
                     ]
                   },
                   { "major": 0, "minor": 0, "patch": 0, "day": 1, "month": 2, "year": 2019, "type": 2, "license": 2,
                     "platforms": [
                       { "name": "Windows", "supported": "Windows 7 and later",
                         "files": [
                           { "extension": ".exe" }, { "extension": ".zip" }
                         ]
                       },
                       { "name": "Linux", "supported": "Ubuntu 16.04 LTS (Xenial Xerus) and later",
                         "files": [
                           { "extension": ".tar.gz" }
                         ]
                       },
                       { "name": "macOS", "supported": "macOS 10.12 (Sierra) and later",
                         "files": [
                           { "extension": ".dmg" }, { "extension": ".zip" }
                         ]
                       }
                     ],
                     "changes": [
                       { "change": "<strong>General:</strong> upgraded to Qt 5.12.0 LTS (see issue <a href=\"https://github.com/opencor/opencor/issues/1910\">#1910</a>)." },
                       { "change": "<strong>COMBINE support:</strong> now recognise files that have a master attribute of \"1\" rather than \"true\" (see issue <a href=\"https://github.com/opencor/opencor/issues/1912\">#1912</a>)." },
                       { "change": "<strong>Graph Panel widget:</strong> fixed a small problem with the scale range of an axis in some cases (see issue <a href=\"https://github.com/opencor/opencor/issues/1941\">#1941</a>)." },
                       { "change": "<strong>CellML Annotation view:</strong> prevent OpenCOR from crashing after a <a href=\"https://cellml.org/\">CellML</a> file has been rendered invalid (see issue <a href=\"https://github.com/opencor/opencor/issues/1958\">#1958</a>)." },
                       { "change": "<strong>CellML Text view:</strong> improved Unicode support (see issue <a href=\"https://github.com/opencor/opencor/issues/1926\">#1926</a>)." },
                       { "change": "<strong>CellML tools:</strong> can now validate a <a href=\"https://cellml.org/\">CellML</a> file from the <a href=\"https://en.wikipedia.org/wiki/Command-line_interface\">CLI</a> (see issue <a href=\"https://github.com/opencor/opencor/issues/1964\">#1964</a>)." },
                       { "change": "<strong>Simulation Experiment view:</strong> added basic support for the import of external data (see issue <a href=\"https://github.com/opencor/opencor/issues/1845\">#1845</a>). Ensure that graph panels are always properly aligned (see issue <a href=\"https://github.com/opencor/opencor/issues/1956\">#1956</a>). Fixed various issues with saving a file under a new name (see issue <a href=\"https://github.com/opencor/opencor/issues/1967\">#1967</a>)." },
                       { "change": "<strong>Third-party libraries:</strong> upgraded <a href=\"https://llvm.org/\">LLVM</a>+<a href=\"https://clang.llvm.org/\">Clang</a> to version 7.0.1 (see issue <a href=\"https://github.com/opencor/opencor/issues/1917\">#1917</a>). Upgraded the <a href=\"https://computation.llnl.gov/projects/sundials\">SUNDIALS</a> library to version 4.0.2 (see issue <a href=\"https://github.com/opencor/opencor/issues/1960\">#1960</a>). Upgraded the <a href=\"http://qwt.sourceforge.net/\">Qwt</a> library to version 6.1.4 (see issue <a href=\"https://github.com/opencor/opencor/issues/1933\">#1933</a>). Upgraded <a href=\"https://mesa3d.org/\">Mesa</a> to version 18.2.8 (see issue <a href=\"https://github.com/opencor/opencor/issues/1945\">#1945</a>)." }
                     ]
                   }
                 ]
               };
