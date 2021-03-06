#include "ofVboMesh.h"

ofVboMesh::ofVboMesh(){
	usage= GL_STATIC_DRAW;
}

ofVboMesh::ofVboMesh(const ofMesh & mom)
:ofMesh(mom)
{
	usage= GL_STATIC_DRAW;
}

void ofVboMesh::setUsage(int _usage){
	usage = _usage;
}

void ofVboMesh::draw(ofPolyRenderMode drawMode){
	if(!vbo.getIsAllocated()){
		if(getNumVertices()){
			vbo.setVertexData(getVerticesPointer(),getNumVertices(),usage);
		}
		if(getNumColors()){
			vbo.setColorData(getColorsPointer(),getNumColors(),usage);
		}
		if(getNumNormals()){
			vbo.setNormalData(getNormalsPointer(),getNumNormals(),usage);
		}
		if(getNumTexCoords()){
			vbo.setTexCoordData(getTexCoordsPointer(),getNumTexCoords(),usage);
		}
		if(getNumIndices()){
			vbo.setIndexData(getIndexPointer(),getNumIndices(),usage);
		}
		vboNumIndices = getNumIndices();
		vboNumVerts = getNumVertices();
		vboNumColors = getNumColors();
		vboNumTexCoords = getNumTexCoords();
		vboNumNormals = getNumNormals();
	}

	if(haveVertsChanged()){
		if(vboNumVerts<getNumVertices()){
			vbo.setVertexData(getVerticesPointer(),getNumVertices(),usage);
			vboNumVerts = getNumVertices();
		}else{
			vbo.updateVertexData(getVerticesPointer(),getNumVertices());
		}
	}
	if(haveColorsChanged()){
		if(vboNumColors<getNumColors()){
			vbo.setColorData(getColorsPointer(),getNumColors(),usage);
			vboNumColors = getNumColors();
		}else{
			vbo.updateColorData(getColorsPointer(),getNumColors());

		}
	}
	if(haveNormalsChanged()){
		if(vboNumNormals<getNumNormals()){
			vbo.updateNormalData(getNormalsPointer(),getNumNormals());
			vboNumNormals = getNumNormals();
		}else{
			vbo.setNormalData(getNormalsPointer(),getNumNormals(),usage);
		}
	}
	if(haveTexCoordsChanged()){
		if(vboNumTexCoords<getNumTexCoords()){
			vbo.setTexCoordData(getTexCoordsPointer(),getNumTexCoords(),usage);
			vboNumTexCoords = getNumTexCoords();
		}else{
			vbo.updateTexCoordData(getTexCoordsPointer(),getNumTexCoords());
		}
	}
	if(haveIndicesChanged()){
		if(vboNumIndices<getNumIndices()){
			vbo.setIndexData(getIndexPointer(),getNumIndices(),usage);
			vboNumIndices = getNumIndices();
		}else{
			vbo.updateIndexData(getIndexPointer(),getNumIndices());
		}
	}


	GLuint mode = ofGetGLPrimitiveMode(getMode());
#ifndef TARGET_OPENGLES
	glPushAttrib(GL_POLYGON_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, ofGetGLPolyMode(drawMode));
	if(getNumIndices() && drawMode!=OF_MESH_POINTS){
		vbo.drawElements(mode,getNumIndices());
	}else{
		vbo.draw(mode,0,getNumVertices());
	}
	glPopAttrib();
#else
	if(drawMode == OF_MESH_POINTS){
		vbo.draw(GL_POINTS,0,getNumVertices());
	}else if(drawMode == OF_MESH_WIREFRAME){
		if(getNumIndices()){
			vbo.drawElements(GL_LINES,getNumIndices());
		}else{
			vbo.draw(GL_LINES,0,getNumVertices());
		}
	}else{
		if(getNumIndices() && drawMode!=OF_MESH_POINTS){
			vbo.drawElements(mode,getNumIndices());
		}else{
			vbo.draw(mode,0,getNumVertices());
		}
	}
#endif


}
