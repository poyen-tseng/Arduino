import peasy.*;
import toxi.geom.*;
import toxi.processing.*;

int maxWalkers = 500;
int currentWalkerIndex = 0;
Walker[] walkers = new Walker[maxWalkers];

int maxSteps = 50;
float defaultStepSize = 20;
int fieldWidth = 500;
int fieldHeight = 500;
int strokeWeight = 10;

class Walker {

  Vec3D lastPoint;
  Vec3D velocity;
    
  Line3D[] lines;
  
  int len = 0;


  Walker(Vec3D _pos) {
    lines = new Line3D[maxSteps];
    lastPoint = _pos;
    velocity = Vec3D.randomVector().scale(1, 1, 0);
    walkers[currentWalkerIndex++] = this;
  }

  void walk() {
    walk(defaultStepSize);
  }
  
  void walk(float stepSize) {
    if (stepSize <= 1) return;
    if (len == maxSteps) return; 
    
    Vec3D nextPoint = lastPoint.add(velocity.scale(stepSize));
    println(velocity);
    Line3D line = new Line3D(lastPoint, nextPoint);
    
    Vec3D point = getIntersectionPoint(line, top);
    Line3D collisionLine = top;
    if (point == null) {
        point = getIntersectionPoint(line, bottom);
        collisionLine = bottom;
    }
    if (point == null) {
        point = getIntersectionPoint(line, left);
        collisionLine = left;
    }
    if (point == null) {
        point = getIntersectionPoint(line, right);
        collisionLine = right;
    }
    if (point == null || lastPoint.equals(point)) {
      lastPoint = nextPoint;
      lines[len++] = line; 
    } else {
       line = new Line3D(lastPoint, point);
       lastPoint = point;
       lines[len++] = line;
       velocity = getReflection(velocity, line, collisionLine, stepSize);
       walk(stepSize - line.getLength());  
    }
    
  }

  void drawPath() {
    strokeWeight(1);
    stroke(255,0,0);
    for (int i = 0; i < len; ++i) {
      g.line(lines[i]);
    }
  }
}


Vec3D getReflection(Vec3D velocity, Line3D line, Line3D border, float stepSize) {
  return new Vec3D(0, -1, 0);
  /*Vec3D normal = border.getNormal();
   Vec3D incidence = line.b.scale(-1).getNormalized() ;
   
   float dot = incidence.dot(normal);
   Vec3D result = new Vec3D(2*normal.x*dot - incidence.x, 2*normal.y*dot - incidence.y,0).scale(stepSize);
   println(result);
   println(line.b);
   println(line.b.getNormalized().angleBetween(result.getNormalized()));
   return result.angleBetween(line.b);
  */ 
}

Vec3D getIntersectionPoint(Line3D a, Line3D b) {
  Line3D.LineIntersection closestLine = a.closestLineTo(b);
  float[] coeff = closestLine.getCoefficients();
  if (!closestLine.getType().equals(Line3D.LineIntersection.Type.valueOf("INTERSECTING")))
    return null;

  if ((int)closestLine.getLength() == 0 && 
      coeff[0] >= 0 && coeff[0] <= 1 &&
      coeff[1] >= -1 && coeff[1] <= 0) {
        return closestLine.getLine().a;
  }
  
  return null;
}
