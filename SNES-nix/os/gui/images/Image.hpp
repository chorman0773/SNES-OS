#ifndef __Image_hpp_2018_05_11_13_54
#define __Image_hpp_2018_05_11_13_54

class Graphics;

class Color{
private:
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
public:
    Color(unsigned char,unsigned char,unsigned char,unsigned char=0);
    explicit Color(unsigned int);
    Color();
    unsigned short toSnesColor();
    unsigned char getRed();
    unsigned char getGreen();
    unsigned char getBlue();
    unsigned char getAlpha();
    unsigned int getRGBA();
};



class Image{
public:
  virtual void draw(Graphics&)const=0;
  virtual void draw(Graphics&,int,int)const=0;
  virtual void draw(Graphics&,int,int,int,int)const=0;
  virtual int getWidth()const=0;
  virtual int getHeight()const=0;
  virtual ~Image();
};

class BufferedImage:public Image{
private:
  int w;
  int h;
  Color* colorMap;
public:
  BuferredImage(Color*,int,int);
  ~BufferedImage();
  const Color* operator[](size_t)const;
  int getWidth()const;
  int getHeight()const;
  void draw(Graphics&)const;
  void draw(Graphics&,int,int)const;
  void draw(Graphics&,int,int,int,int)const;
};

class NativeBufferedImage:public Image{
private:
  int w;
  int h;
  unsigned char pallateSize;
  unsigned char* pallate;
  unsigned char* gfxTable;
public:
   NativeBufferedImage(int,int,unsigned char,unsigned char*,unsigned char*);
   int getWidth()const;
   int getHeight()const;
   const unsigned char* operator [](size_t)const;
   const unsigned char* getPallate()const;
   void draw(Graphics&)const;
   void draw(Graphics&,int,int)const;
   void draw(Graphics&,int,int,int,int)const;
};

class NativeImage:public Image{
private:
  void* gfxLocation;
public:
  NativeImage(const NativeBufferedImage&);
  NativeImage(const BufferedImage&);
  int getWidth()const;
  int getHeight()const;
  void draw(Graphics&)const;
  void draw(Graphics&,int,int)const;
  void draw(Graphics&,int,int,int,int)const;
};



#endif
