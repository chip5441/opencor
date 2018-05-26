/*******************************************************************************

Copyright (C) The University of Auckland

OpenCOR is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenCOR is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

//==============================================================================
// Jupyter kernel plugin
//==============================================================================

#pragma once

//==============================================================================

#include "cliinterface.h"
#include "eventloopinterface.h"
#include "plugininfo.h"

//==============================================================================

namespace OpenCOR {
namespace JupyterKernel {

//==============================================================================

PLUGININFO_FUNC JupyterKernelPluginInfo();

//==============================================================================

class JupyterKernelPlugin : public QObject, public CliInterface,
                            public EventLoopInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "OpenCOR.JupyterKernelPlugin" FILE "jupyterkernelplugin.json")

    Q_INTERFACES(OpenCOR::CliInterface)
    Q_INTERFACES(OpenCOR::EventLoopInterface)

public:
#include "cliinterface.inl"
#include "eventloopinterface.inl"

private:
    void runHelpCommand();
    int runKernel(const QStringList &pArguments);
};

//==============================================================================

}   // namespace JupyterKernel
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
