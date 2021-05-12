/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "mitkMouseModeSwitcher.h"
// us
#include "usGetModuleContext.h"
#include "usModuleContext.h"

#include "mitkInteractionEventObserver.h"

namespace mitk
{
  itkEventMacroDefinition(MouseModeChangedEvent, itk::AnyEvent);
}

mitk::MouseModeSwitcher::MouseModeSwitcher()
  : m_ActiveInteractionScheme(MITK), m_ActiveMouseMode(MousePointer), m_CurrentObserver(nullptr)
{
  this->InitializeListeners();
  this->SetInteractionScheme(m_ActiveInteractionScheme);
}

mitk::MouseModeSwitcher::~MouseModeSwitcher()
{
  m_ServiceRegistration.Unregister();
}

void mitk::MouseModeSwitcher::InitializeListeners()
{
  if (m_CurrentObserver.IsNull())
  {
    m_CurrentObserver = mitk::DisplayInteractor::New();
    m_CurrentObserver->LoadStateMachine("DisplayInteraction.xml");
    m_CurrentObserver->SetEventConfig("DisplayConfigMITK.xml");
    // Register as listener via micro services
    us::ServiceProperties props;
    props["name"] = std::string("DisplayInteractor");
    m_ServiceRegistration =
      us::GetModuleContext()->RegisterService<InteractionEventObserver>(m_CurrentObserver.GetPointer(), props);
  }
}

void mitk::MouseModeSwitcher::SetInteractionScheme(InteractionScheme scheme)
{
  switch (scheme)
  {
    case MITK:
    {
      m_CurrentObserver->SetEventConfig("DisplayConfigMITK.xml");
    }
    break;
    case PACS:
    {
      m_CurrentObserver->SetEventConfig("DisplayConfigPACS.xml");
    }
    break;

    case ROTATION:
    {
      m_CurrentObserver->SetEventConfig("DisplayConfigMITKRotationUnCoupled.xml");
    }
    break;

    case ROTATIONLINKED:
    {
      m_CurrentObserver->SetEventConfig("DisplayConfigMITKRotation.xml");
    }
    break;

    case SWIVEL:
    {
      m_CurrentObserver->SetEventConfig("DisplayConfigMITKSwivel.xml");
    }
    break;
  }
  m_ActiveInteractionScheme = scheme;
  this->InvokeEvent(MouseModeChangedEvent());
}

void mitk::MouseModeSwitcher::SelectMouseMode(MouseMode mode)
{
  if (m_ActiveInteractionScheme != PACS)
    return;

  switch (mode)
  {
    case MousePointer:
    {
      m_CurrentObserver->SetEventConfig("DisplayConfigPACS.xml");
      break;
    } // case 0
    case Scroll:
    {
      m_CurrentObserver->AddEventConfig("DisplayConfigPACSScroll.xml");

      break;
    }
    case LevelWindow:
    {
      m_CurrentObserver->AddEventConfig("DisplayConfigPACSLevelWindow.xml");
      break;
    }
    case Zoom:
    {
      m_CurrentObserver->AddEventConfig("DisplayConfigPACSZoom.xml");
      break;
    }
    case Pan:
    {
      m_CurrentObserver->AddEventConfig("DisplayConfigPACSPan.xml");
      break;
    }
  } // end switch (mode)
  m_ActiveMouseMode = mode;
  this->InvokeEvent(MouseModeChangedEvent());
}

mitk::MouseModeSwitcher::MouseMode mitk::MouseModeSwitcher::GetCurrentMouseMode() const
{
  return m_ActiveMouseMode;
}
