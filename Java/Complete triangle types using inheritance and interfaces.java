
/*
* @author: Mujtaba Ali
*/


abstract class Triangle
{
    abstract public void setSides(double s1,double s2,double s3);
    abstract public double getAlpha();
    abstract public double getBeta();
    abstract public double getGamma();
    abstract public double getArea();
    abstract public String getTriangleType();
}


interface Acute
{
    boolean ifAcute();
    String getAcuteType();
}

interface Right
{
    boolean ifRight();
    String getRightType();
}

interface Obtuse
{
    boolean ifObtuse();
    String getObtuseType();
}


class Equilateral extends Triangle
{
  private double side1,side2,side3;
  public void setSides(double s1,double s2,double s3){
      if(s1==s2 && s2==s3){
          side1=s1;
          side2=s2;
          side3=s3;
          return;
        }
        else{
            System.out.println("All sides must be equal");
            return;
        }
    }

    public double getArea(){
        double s=(side1+side2+side3)/2;
        return Math.sqrt(s*(s-side1)*(s-side2)*(s-side3));
    }
    public double getAlpha(){
        return Math.toDegrees(Math.acos(((Math.pow(side1,2)+Math.pow(side2,2)-Math.pow(side3,2))/(2*side1*side2))));
    }
    public double getBeta(){
    	return Math.toDegrees(Math.acos(((Math.pow(side1,2)+Math.pow(side3,2)-Math.pow(side2,2))/(2*side1*side3))));
    }
    public double getGamma(){
    	return Math.toDegrees(Math.acos(((Math.pow(side3,2)+Math.pow(side2,2)-Math.pow(side1,2))/(2*side3*side2))));
    }
    public String getTriangleType(){
        return "Equilateral";
    }
}


class Scalene extends Triangle implements Acute, Right, Obtuse
{
   private double side1,side2,side3;
    // The following are inherited from Triangle abstract class
    public void setSides(double s1,double s2,double s3){
        if(s1!=s2 && s1!=s3 && s2!=s3){
        side1=s1;
        side2=s2;
        side3=s3;
        return;
    }
    else{
        System.out.println("Not Scalene");
        return;
    }
    }
    public double getArea(){
        double s=(side1+side2+side3)/2;
        return Math.sqrt(s*(s-side1)*(s-side2)*(s-side3));
    }
    public double getAlpha(){
        return Math.toDegrees(Math.acos(((Math.pow(side1,2)+Math.pow(side2,2)-Math.pow(side3,2))/(2*side1*side2))));
    }
    public double getBeta(){
    	return Math.toDegrees(Math.acos(((Math.pow(side1,2)+Math.pow(side3,2)-Math.pow(side2,2))/(2*side1*side3))));
    }
    public double getGamma(){
    	return Math.toDegrees(Math.acos(((Math.pow(side3,2)+Math.pow(side2,2)-Math.pow(side1,2))/(2*side3*side2))));
    }
    public String getTriangleType(){
        String scal="Scalene";
        String result="";
        if(ifAcute()==true){
            result=getAcuteType()+scal;
            return result;
        }
        if(ifRight()==true){
            result=getRightType()+scal;
            return result;
        }
        if(ifObtuse()==true){
            result= getObtuseType()+scal;
           return result;
        }
        return "";
    }
    // The following are inherited from interfaces
    public boolean ifAcute(){
        if(getAlpha()<90 && getBeta()<90 && getGamma()<90)
        return true;
        else
        return false;
    }
    public boolean ifRight(){
        if(getAlpha()==90 || getBeta()==90 || getGamma()==90)
        return true;
        else
        return false;
    }
    public boolean ifObtuse(){
        if(getAlpha()>90 || getBeta()>90 || getGamma()>90)
        return true;
        else
        return false;
    }
    public String getAcuteType(){
        return "Acute ";
    }
    public String getRightType(){
        return "Right ";
    }
    public String getObtuseType(){
        return "Obtuse ";
    }
}


class Isosceles extends Triangle implements Acute, Right, Obtuse
{
    private double side1,side2,side3;
    // The following are inherited from the Triangle abstract class
    public void setSides(double s1,double s2,double s3){
        if((s1==s2 && s1!=s3) || (s1==s3 && s1!=s2) || (s2==s3 && s2!=s1)){
        side1=s1;
        side2=s2;
        side3=s3;
        return;
    }
    else{
        System.out.println("Not Isosceles");
        return;
    }
    }
    public double getArea(){
        double s=(side1+side2+side3)/2;
        return Math.sqrt(s*(s-side1)*(s-side2)*(s-side3));
    }
    public double getAlpha(){
        return Math.toDegrees(Math.acos(((Math.pow(side1,2)+Math.pow(side2,2)-Math.pow(side3,2))/(2*side1*side2))));
    }
    public double getBeta(){
    	return Math.toDegrees(Math.acos(((Math.pow(side1,2)+Math.pow(side3,2)-Math.pow(side2,2))/(2*side1*side3))));
    }
    public double getGamma(){
    	return Math.toDegrees(Math.acos(((Math.pow(side3,2)+Math.pow(side2,2)-Math.pow(side1,2))/(2*side3*side2))));
    }
    public String getTriangleType(){
    String iso="Isosceles";
        String result="";
        if(ifAcute()==true){
            result=getAcuteType()+iso;
            return result;
        }
        if(ifRight()==true){
            result=getRightType()+iso;
            return result;
        }
        if(ifObtuse()==true){
            result= getObtuseType()+iso;
           return result;
        }
        return "";
    }
    // The following are inherited from the interfaces
     public boolean ifAcute(){
        if(getAlpha()<90 && getBeta()<90 && getGamma()<90)
        return true;
        else
        return false;
    }
    public boolean ifRight(){
        if(getAlpha()==90 || getBeta()==90 || getGamma()==90)
        return true;
        else
        return false;
    }
    public boolean ifObtuse(){
        if(getAlpha()>90 || getBeta()>90 || getGamma()>90)
        return true;
        else
        return false;
    }
    public String getAcuteType(){
        return "Acute ";
    }
    public String getRightType(){
        return "Right ";
    }
    public String getObtuseType(){
        return "Obtuse ";
    }
}

public class abc {
	public static void main(String[] args) {
		Equilateral eq=new Equilateral();
		eq.setSides(15, 15, 15);
		System.out.println("Type : "+eq.getTriangleType());
		System.out.println("Area : "+eq.getArea());
		System.out.println("Alpha : "+eq.getAlpha());
		System.out.println("Beta : "+eq.getBeta());
		System.out.println("Gamma : "+eq.getGamma());
		System.out.println();

		Scalene scal=new Scalene();
		scal.setSides(3, 4, 5);
		System.out.println("Type : "+scal.getTriangleType());
		System.out.println("Area : "+scal.getArea());
		System.out.println("Alpha : "+scal.getAlpha());
		System.out.println("Beta : "+scal.getBeta());
		System.out.println("Gamma : "+scal.getGamma());
		System.out.println();

		Isosceles iso=new Isosceles();
		iso.setSides(10, 19, 10);
		System.out.println("Type : "+iso.getTriangleType());
		System.out.println("Area : "+iso.getArea());
		System.out.println("Alpha : "+iso.getAlpha());
		System.out.println("Beta : "+iso.getBeta());
		System.out.println("Gamma : "+iso.getGamma());
	}

}


        Output:

        Type : Equilateral
        Area : 97.42785792574935
        Alpha : 60.00000000000001
        Beta : 60.00000000000001
        Gamma : 60.00000000000001

        Type : Right Scalene
        Area : 6.0
        Alpha : 90.0
        Beta : 53.13010235415598
        Gamma : 36.86989764584401

        Type : Obtuse Isosceles
        Area : 29.663740492392392
        Alpha : 18.194872338766785
        Beta : 143.61025532246646
        Gamma : 18.194872338766785
