#ifndef __Image_hpp_2018_05_11_13_54
#define __Image_hpp_2018_05_11_13_54

class Graphics;




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



#endif
