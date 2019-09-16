#include "m4gfx/sis/predef.hpp"
#include "m4gfx/sis/info_provider.hpp"
#include <GL/glew.h>
#include "gpuinfo.hpp"



template<>
void m4gfx::typed_info_provider<m4gfx::XIC_GPU>::build() {
  GLuint err;
  glew::createParams params =
  {
#if defined(_WIN32)
    -1,  /* pixelformat */
#elif !defined(__HAIKU__) && !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
    "",  /* display */
    -1,  /* visual */
#endif
    0,   /* major */
    0,   /* minor */
    0,   /* profile mask */
    0,   /* flags */
    0    /* experimental */
  };
  
#if defined(GLEW_EGL)
  typedef const GLubyte* (GLAPIENTRY * PFNGLGETSTRINGPROC) (GLenum name);
  PFNGLGETSTRINGPROC getString;
#endif

  if (GL_TRUE == glew::glewCreateContext(&params))
  {
    glew::glewDestroyContext();
    return;
  }
  glewExperimental = params.experimental ? GL_TRUE : GL_FALSE;
  err = glewInit();
  if (GLEW_OK != err)
  {
    glew::glewDestroyContext();
    return;
  }

#if defined(GLEW_EGL)
  getString = (PFNGLGETSTRINGPROC) eglGetProcAddress("glGetString");
  if (!getString)
  {
    glew::glewDestroyContext();
    return;
  }
#endif

    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

#if defined(GLEW_EGL)
    std::string gl_renderer(getString(GL_RENDERER))
    std::string gl_vendor(getString(GL_VENDOR));
    std::string gl_version(getString(GL_VERSION));
    std::string gl_sl(getString(GL_SHADING_LANGUAGE_VERSION));
#else
  
    std::string gl_renderer((char*)::glGetString(GL_RENDERER));
    std::string gl_vendor((char*)::glGetString(GL_VENDOR));
    std::string gl_version((char*)::glGetString(GL_VERSION));
    std::string gl_sl((char*)::glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

    rapidjson::Value gl_renderer_value(gl_renderer, allocator);
    d.AddMember("renderer",gl_renderer_value,allocator);
    rapidjson::Value gl_vendor_value(gl_vendor, allocator);
    d.AddMember("vendor",gl_vendor_value,allocator);
    rapidjson::Value gl_version_value(gl_version, allocator);
    d.AddMember("version",gl_version_value,allocator);
    rapidjson::Value gl_sl_value(gl_sl, allocator);
    d.AddMember("shadinglanguage",gl_sl_value,allocator);
    
    glew::clear_document();
    glew::glewInfo();
#if defined(GLEW_EGL)
    glew::eglewInfo();
#elif defined(_WIN32)
    glew::wglewInfo();
#else
    glew::glxewInfo();
#endif
    glew::glewDestroyContext();
    
    rapidjson::Document features;
    features.SetObject();
    
    glew::get_document(features);
    std::string namespace_prefix(glew::get_namespace_prefix());
    rapidjson::Value gl_namespace_prefix(namespace_prefix, allocator);
    d.AddMember(gl_namespace_prefix,features, allocator);
    info.add_attribute(namespace_prefix);          
    info.insert_json(d);
    info.set_type(m4gfx::XIC_GPU);
}

void GpuInfoProviderFunction ()
{
    m4gfx::typed_info_provider<m4gfx::XIC_GPU> GpuObj;
}