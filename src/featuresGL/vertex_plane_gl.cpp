#include "vertex_plane_gl.h"
#include "vertex_plane.h"
#include <stdio.h>

#ifdef G2O_HAVE_OPENGL
#include "g2o/stuff/opengl_wrapper.h"
#endif

#include <Eigen/SparseCore>
#include <typeinfo>

namespace g2o {

#ifdef G2O_HAVE_OPENGL
   VertexPlane3dDrawAction::VertexPlane3dDrawAction(): DrawAction(typeid(VertexPlane3d).name()){
   }

   bool VertexPlane3dDrawAction::refreshPropertyPtrs(HyperGraphElementAction::Parameters* params_){
      if (! DrawAction::refreshPropertyPtrs(params_))
         return false;
      if (_previousParams){
         _pointSize = _previousParams->makeProperty<FloatProperty>(_typeName + "::POINT_SIZE", 1.);
      } else {
         _pointSize = 0;
      }
      return true;
   }


   HyperGraphElementAction* VertexPlane3dDrawAction::operator()(HyperGraph::HyperGraphElement* element,
           HyperGraphElementAction::Parameters* params ){

      if (typeid(*element).name()!=_typeName)
         return 0;
      refreshPropertyPtrs(params);
      if (! _previousParams)
         return this;

      if (_show && !_show->value())
         return this;
      VertexPlane3d* that = static_cast<VertexPlane3d*>(element);


      glPushAttrib(GL_ENABLE_BIT | GL_POINT_BIT);
      glDisable(GL_LIGHTING);
      glColor3f(0.8f,0.5f,0.3f);
      if (_pointSize) {
         glPointSize(_pointSize->value());
      }
      //    glBegin(GL_POINTS);
      glBegin(GL_LINES);
      glVertex3f((float)that->estimate()(0),(float)that->estimate()(1),(float)that->estimate()(2));
      glEnd();
      glPopAttrib();

      return this;
   }
#endif

}