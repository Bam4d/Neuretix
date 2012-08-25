
class GLEngine
{
public:
	GLEngine(void);
	~GLEngine(void);

	int DrawLine(float x1,float y1,float z1,float x2,float y2,float z2,float r,float g,float b);
	int DrawPoint(float x,float y,float z,float r,float g,float b,float size);
	int DrawFilledSquare(float,float,float,float,float ,float ,float);
	int DrawCube(float,float,float,float,float r,float g,float b);
	void DrawText(float x,float y,float r,float g,float b,char buf[]);
	void DrawCurve(GLfloat*,int,int,float, float, float);

	void KillGLWindow();
	int CreateGLWindow(char*,int, int);
	void SwapBuffer();
	void BeginRender();
	void Clear();

        void KeyPressed(unsigned char,int, int);

	void ReSizeGLScene(int,int);
        void ResetGLScene();
	static GLfloat CalcPan(int, int);
	static GLfloat CalcRot(int, int);
	static GLfloat CalcZoom(int);
	int nmx,nmy; //previouse positions of mouse and new positions
	int zDelta; //mouse wheel position indicator
	bool active;		// Window Active Flag Set To TRUE By Default
	bool mouse_but_right;
	bool mouse_but_left;
	GLfloat windowposx,windowposy,windowposz; //position of projection matrix
	GLfloat windowrotx,windowroty; //rotations of the projection matrix
	int pmx,pmy;
	
	GLuint		base;
	bool fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default

private:
	void ChangePerspective(GLfloat x, GLfloat y, GLfloat z); //change the viewpoint/perspective
	int InitGL(); //Initiate the OpenGL engine
	void TranslateP();
	void BuildFont();// Build Our Bitmap Font
	void KillFont();// Delete The Font List
	void glPrint(const char *fmt, ...); //custom opengl character printing
	int sc_height, sc_width; //screen width and height

        int window;
	

	
};
