#include "mitkRESTServerMicroService.h"
#include <mitkCommon.h>

mitk::RESTServerMicroService::RESTServerMicroService(web::uri uri) : m_Listener(uri)
{
  m_Uri = uri;
}

mitk::RESTServerMicroService::~RESTServerMicroService()
{
}

void mitk::RESTServerMicroService::OpenListener()
{
    //create listener
    m_Listener = MitkListener(m_Uri);
    //Connect incoming get requests with HandleGet method
    m_Listener.support(web::http::methods::GET,
                       std::bind(&mitk::RESTServerMicroService::HandleGet, this, std::placeholders::_1));
    //open listener
    m_Listener.open().wait();
}

void mitk::RESTServerMicroService::CloseListener()
{
  //close listener
  m_Listener.close().wait();
}

web::uri mitk::RESTServerMicroService::GetUri() 
{
  return m_Uri;
}

void mitk::RESTServerMicroService::HandleGet(MitkRequest request)
{
  int port = m_Listener.uri().port();
 //getting exact request uri has to be a parameter in handle function
  web::uri_builder build(m_Listener.uri());
  build.append(request.absolute_uri());
  utility::string_t uriStringT = build.to_uri().to_string();

  std::string uriString(uriStringT.begin(), uriStringT.end());
  MITK_INFO << "Get Request fot server at port " << port << " Exact request uri: " << uriString;
  
  web::json::value content;
  //get RESTManager as microservice to call th Handle method of the manager
  us::ModuleContext *context = us::GetModuleContext();

  auto managerRef = context->GetServiceReference<IRESTManager>();
  if (managerRef)
  {
    auto managerService = context->GetService(managerRef);
    if (managerService)
    {
      web::json::value data = request.extract_json().get();
      MITK_INFO << "Server: Data send to manager";
      //call the handle method
      content = managerService->Handle(build.to_uri(), data);
      MITK_INFO << "server: Data received from manager";
    }
  }
  if (content!=NULL)
  {
    //content handled by observer
    request.reply(MitkRestStatusCodes::OK, content);
  }
  else
  {
    //no observer to handle data
    request.reply(MitkRestStatusCodes::NotFound);
  }
}