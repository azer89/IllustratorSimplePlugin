

#include "GLWidget.h"

#include <iostream>
#include <random>
#include <math.h>

#include <QGLFormat>
#include <QSvgGenerator>

// for forward declaration
#include "AVector.h"
#include "ALine.h"
#include "ATriangle.h"
#include "ABox.h"
#include "VertexData.h"
#include "VertexDataHelper.h"
#include "PathIO.h"

#include "SystemParams.h"

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

GLWidget::GLWidget(QGLFormat format, QWidget *parent) :
    QGLWidget(format, parent),
    _vDataHelper(0),
	_pathIO(0),
    _isMouseDown(false),
    _zoomFactor(1.0),
    _img_width(500),
    _img_height(500),
    _slice(8),
    _shaderProgram(0),
	_imgID(0),
	_isGLInitialized(false)
{
}

GLWidget::~GLWidget()
{
	if (_vDataHelper)	{ delete _vDataHelper; }
	if (_pathIO)		{ delete _pathIO; }
	if (_shaderProgram) { delete _shaderProgram; }
}

void GLWidget::initializeGL()
{
	/* OpenGL format */
    QGLFormat glFormat = QGLWidget::format();
    if (!glFormat.sampleBuffers()) 
	{ 
		//std::cerr << "Could not enable sample buffers." << std::endl; 
		textEdit->append("Could not enable sample buffers.");
		return; 
	}

	/* Stuff I forget what their purposes are */
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glEnable(GL_DEPTH_TEST);

	/* Shaders */
    _shaderProgram = new QOpenGLShaderProgram();
    if (!_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, SystemParams::v_shader_file.c_str()))
    { 
		//std::cerr << "Cannot load vertex shader." << std::endl; 
		textEdit->append("Cannot load vertex shader.");
		return; 
	}
    if (!_shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, SystemParams::f_shader_file.c_str()))
    { 
		//std::cerr << "Cannot load fragment shader." << std::endl; 
		textEdit->append("Cannot load fragment shader.");
		return; 
	}
    if ( !_shaderProgram->link() )
    { 
		//std::cerr << "Cannot link shaders." << std::endl; 
		textEdit->append("Cannot link shaders.");
		return; 
	}
    _shaderProgram->bind();
    _mvpMatrixLocation = _shaderProgram->uniformLocation("mvpMatrix");
    _colorLocation = _shaderProgram->attributeLocation("vertexColor");
    _vertexLocation = _shaderProgram->attributeLocation("vert");
    _use_color_location = _shaderProgram->uniformLocation("use_color");

	/* for VBO and VAO */
    _vDataHelper = new VertexDataHelper(_shaderProgram);
	_pathIO = new PathIO();

	// comment these
    //CreateCurve();
    //BuildCurveVertexData();

	// You want image or the actual path ?
	//SetImage(QString::fromStdString(SystemParams::temp_png_location));
	if (!_pathsVao.isCreated() && _paths.size() > 0)
	{
		InitializePaths();
	}

	// a box
	_boxes.push_back(ABox(AVector(0, 0),
						  AVector(0, this->_img_height),
						  AVector(this->_img_width, 0),
						  AVector(this->_img_width, this->_img_height)));
	_vDataHelper->BuildQuadsVertexData(_boxes, &_boxVbo, &_boxVao);

	// an example how to render a triangle
	//_triangles.push_back(ATriangle(AVector(1, 1), AVector(25, 25), AVector(1, 50)));
	//_vDataHelper->BuildTrianglesVertexData(_triangles, &_triangleVbo, &_triangleVao, QVector3D(1.0, 0.25, 0.25));

	// don't remove this
	textEdit->append("OpenGL is initialized");
	_isGLInitialized = true;
}

bool GLWidget::event( QEvent * event )
{
    return QGLWidget::event(event);
}

// This is an override function from Qt but I can't find its purpose
void GLWidget::resizeGL(int width, int height)
{
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, this->width(),  this->height());

    int current_width = width();
    int current_height = height();

    // Set orthographic Matrix
	// the y axis is flipped because the origin is at the top-left corner
    QMatrix4x4 orthoMatrix;
    orthoMatrix.ortho(0.0 +  _scrollOffset.x(),
                      (float)current_width +  _scrollOffset.x(),
                      (float)current_height + _scrollOffset.y(),
                      0.0 + _scrollOffset.y(),
                      -100, 100);

    // Translate the view to the middle
    QMatrix4x4 transformMatrix;
    transformMatrix.setToIdentity();
    transformMatrix.scale(_zoomFactor);

    _shaderProgram->setUniformValue(_mvpMatrixLocation, orthoMatrix * transformMatrix);

	if (_pathsDataSize > 0)
	{
		//std::cout << "draw paths\n";
		_shaderProgram->setUniformValue(_use_color_location, (GLfloat)1.0);

		glLineWidth(5.0f);
		_pathsVao.bind();
		glDrawArrays(GL_LINES, 0, _pathsDataSize);
		_pathsVao.release();
	}

    PaintCurve();

	// A triangle
	if (_triangleVao.isCreated())
	{
		_shaderProgram->setUniformValue(_use_color_location, (GLfloat)1.0);
		_triangleVao.bind();
		glDrawArrays(GL_TRIANGLES, 0, _triangles.size() * 3);
		_triangleVao.release();
	}

	// A box
	if (_imgID)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _imgID);
		if (_boxVao.isCreated())
		{
			//_shaderProgram->setUniformValue(_use_color_location, (GLfloat)1.0);
			_shaderProgram->setUniformValue(_use_color_location, (GLfloat)0.0);
			_boxVao.bind();
			glDrawArrays(GL_QUADS, 0, _boxes.size() * 4);
			_boxVao.release();
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
}

// Mouse is pressed
void GLWidget::mousePressEvent(int x, int y)
{
    _isMouseDown = true;
	double dx = (x + _scrollOffset.x()) / _zoomFactor;
	double dy = (y + _scrollOffset.y()) / _zoomFactor;

    this->repaint();
}

// Mouse is moved
void GLWidget::mouseMoveEvent(int x, int y)
{
	double dx = (x + _scrollOffset.x()) / _zoomFactor;
	double dy = (y + _scrollOffset.y()) / _zoomFactor;

    // your stuff

    this->repaint();
}


// Mouse is released
void GLWidget::mouseReleaseEvent(int x, int y)
{
    _isMouseDown = false;
	double dx = (x + _scrollOffset.x()) / _zoomFactor;
	double dy = (y + _scrollOffset.y()) / _zoomFactor;

    // your stuff

    this->repaint();
}

void GLWidget::mouseDoubleClick(int x, int y)
{
	double dx = (x + _scrollOffset.x()) / _zoomFactor;
	double dy = (y + _scrollOffset.y()) / _zoomFactor;

    // your stuff

    this->repaint();
}


void GLWidget::HorizontalScroll(int val) { _scrollOffset.setX(val); }
void GLWidget::VerticalScroll(int val) { _scrollOffset.setY(val); }
void GLWidget::ZoomIn() { this->_zoomFactor += 0.5f; }
void GLWidget::ZoomOut() { this->_zoomFactor -= 0.5f; if(this->_zoomFactor < 0.1f) _zoomFactor = 0.1f; }

void GLWidget::AddSlice()
{
    this->_slice++;
    CreateCurve();
    BuildCurveVertexData();

}

void GLWidget::RemoveSlice()
{
    this->_slice--;
    if(this->_slice < 3)
        { this->_slice = 3; }
    CreateCurve();
    BuildCurveVertexData();
}

void GLWidget::CreateCurve()
{
    _points.clear();

    AVector centerPt(this->_img_width / 2, this->_img_height / 2);

	float addValue = (3.14159 * 2.0 / _slice);
	for (float a = 0.0; a < 3.14159 * 2.0; a += addValue)
    {
        float xPt = centerPt.x + 10 * sin(a);
        float yPt = centerPt.y + 10 * cos(a);
        _points.push_back(AVector(xPt, yPt));
    }
}

void GLWidget::BuildCurveVertexData()
{
    // POINTS
    QVector3D vecCol = QVector3D(1.0, 0.0, 0.0);
    _vDataHelper->BuildPointsVertexData(_points, &_pointsVbo, &_pointsVao, vecCol);

    // LINES
    vecCol = QVector3D(0.0, 0.5, 1.0);
    std::vector<ALine> lines;
    for(uint a = 0; a < _points.size(); a++)
    {
        if(a < _points.size() - 1) { lines.push_back(ALine(_points[a], _points[a + 1])); }
        else { lines.push_back(ALine(_points[a], _points[0])); }
    }
    _vDataHelper->BuildLinesVertexData(lines, &_linesVbo, &_linesVao, vecCol);
}

void GLWidget::SaveToSvg()
{
}

void GLWidget::PaintCurve()
{
    if(_points.size() == 0) { return; }

    _shaderProgram->setUniformValue(_use_color_location, (GLfloat)1.0);

    glPointSize(5.0f);
    _pointsVao.bind();
    glDrawArrays(GL_POINTS, 0, _points.size());
    _pointsVao.release();

    glLineWidth(2.0f);
    _linesVao.bind();
    glDrawArrays(GL_LINES, 0, _points.size() * 2);
    _linesVao.release();
}

#define my_min(a,b) ((a)<(b) ? (a) : (b))
#define my_max(a,b) ((a)>(b) ? (a) : (b))

void GLWidget::SetData(int width, int height, std::vector<QColor> colorList)
{
	this->_snapshot_width  = width;
	this->_snapshot_height = height;
	this->_colorList        = colorList;
}

void GLWidget::SaveCurrentPaths(std::string filename)
{
	_pathIO->SavePath(_paths, filename);
}

void GLWidget::LoadPath(std::string filename)
{
	_paths = _pathIO->LoadPath(filename);
	InitializePaths();
	this->repaint();

	std::cout << this->_img_width << " " << this->_img_height << "\n";
}

void GLWidget::SetPaths(std::vector<APath> paths)
{
	this->_paths = paths;
}

void GLWidget::InitializePaths()
{
	// add colors
	for (size_t a = 0; a < _paths.size(); a++)
	{
		double rCol = ((double)rand() / (RAND_MAX));
		double gCol = ((double)rand() / (RAND_MAX));
		double bCol = ((double)rand() / (RAND_MAX));
		_pathsColors.push_back(QVector3D(rCol, gCol, bCol));
	}
	_pathsDataSize = _vDataHelper->BuildPathsVertexData(_paths, &_pathsVbo, &_pathsVao, _pathsColors);

	this->repaint();
}

void GLWidget::SetImage(int width, int height, std::vector<QColor> colorList)
{
	//textEdit->append("width :" + QString::number(width));
	//textEdit->append("height :" + QString::number(height));
	//textEdit->append("colorList size :" + QString::number(colorList.size()));

	bool isLoaded = true;
	_imgOriginal = QImage(width, height, QImage::Format_RGB32);

	// size
	this->_img_width = _imgOriginal.width();
	this->_img_height = _imgOriginal.height();

	for (int x = 0; x < this->_img_width; x++)
	{
		for (int y = 0; y < this->_img_height; y++)
		{
			//int idx = x + y * this->_img_width;
			//QColor col = colorList[idx];
			//QColor col = QColor(0, 255, 0, 255);
			QColor col = QColor(rand() % 255, rand() % 255, rand() % 255, 255);
			_imgOriginal.setPixel(x, y, col.rgba());
		}
	}

	// calculating power-of-two (pow) size
	int xpow = (int)std::pow(2.0, std::ceil(std::log10((double)_img_width) / std::log10(2.0)));
	int ypow = (int)std::pow(2.0, std::ceil(std::log10((double)_img_height) / std::log10(2.0)));

	xpow = my_max(xpow, ypow);	// the texture should be square too
	xpow = my_min(xpow, 1024);	// shrink if the size is too big
	ypow = xpow;

	// transform the image to square pow size
	_imgGL = _imgOriginal.scaled(xpow, ypow, Qt::IgnoreAspectRatio);
	_imgGL = QGLWidget::convertToGLFormat(_imgGL);

	_imgID = 0;

	glBindTexture(GL_TEXTURE_2D, 0); // I just want to make sure...
	//glEnable(GL_TEXTURE_2D); // should I have this ?

	glGenTextures(1, &_imgID);

	if (!_imgID)
	{
		//glGetError 1282 ???
		textEdit->append("glGetError :" + QString::number(glGetError()));
	}

	glBindTexture(GL_TEXTURE_2D, _imgID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _imgGL.width(), _imgGL.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _imgGL.bits());

	//glDisable(GL_TEXTURE_2D);  // should I have this ?
	//textEdit->append("_imgID :" + QString::number(_imgID));
}

void GLWidget::SetImage(QString img)
{
	//bool isLoaded = true;
	//_imgOriginal = QImage(50, 50, QImage::Format_RGB32);
	bool isLoaded = _imgOriginal.load(img);

	// size
	this->_img_width = _imgOriginal.width();
	this->_img_height = _imgOriginal.height();

	/*
	for (int x = 0; x < this->_img_width; x++)
	{
		for (int y = 0; y < this->_img_height; y++)
		{
			//QColor col = QColor(0, 255, 0, 255);
			QColor col = QColor(rand() % 255, rand() % 255, rand() % 255, 255);
			_imgOriginal.setPixel(x, y, col.rgba());
		}
	}*/

	// calculating power-of-two (pow) size
	int xpow = (int)std::pow(2.0, std::ceil(std::log10((double)_img_width) / std::log10(2.0)));
	int ypow = (int)std::pow(2.0, std::ceil(std::log10((double)_img_height) / std::log10(2.0)));

	xpow = my_max(xpow, ypow);	// the texture should be square too
	xpow = my_min(xpow, 1024);	// shrink if the size is too big
	ypow = xpow;

	// transform the image to square pow size
	_imgGL = _imgOriginal.scaled(xpow, ypow, Qt::IgnoreAspectRatio);
	_imgGL = QGLWidget::convertToGLFormat(_imgGL);

	glGenTextures(1, &_imgID);
	glBindTexture(GL_TEXTURE_2D, _imgID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _imgGL.width(), _imgGL.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _imgGL.bits());
}


