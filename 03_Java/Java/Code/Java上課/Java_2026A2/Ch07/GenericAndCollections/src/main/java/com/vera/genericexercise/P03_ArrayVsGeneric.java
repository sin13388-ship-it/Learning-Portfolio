package com.vera.genericexercise;

public class P03_ArrayVsGeneric {

    static void main(String[] args) {

        /*
        * You define a generic type using angle brackets < > with a placeholder letter
        * (commonly T for Type, E for Element, or K, V for Key/Value).
        * Java Generics only support Reference Types (Objects), not primitive types.
        * This is because, under the hood, Java implements Generics using "type erasure,"
        * which converts generic types into Object. Since primitive types are not objects,
        * they cannot be used in that context.
        * The Solution: Wrapper Classes
        * To get around this, Java provides Wrapper Classes.
        * Every primitive type has a corresponding object class that wraps the value.
        * */

        Integer[] integers={1,2,3,4,5,6};
        Double[] doubles={1.1,2.2,3.3,4.4,5.5,6.6};
        Character[] characters={'H','E','L','L','O'};
        displayArray(integers);
        displayArray(doubles);
        displayArray(characters);

        /*Generic*/
        System.out.println("======Generic======");
        displayArrayType(integers);
        displayArrayType(doubles);
        displayArrayType(characters);
    }
    static  void displayArray(Integer[] integers){
        for(var e : integers) {
            System.out.printf("%d\t",e);
        }
        System.out.println();
    }
    static  void displayArray(Double[] doubles){
        for(var e : doubles) {
            System.out.printf("%.3f\t",e);
        }
        System.out.println();
    }
    static  void displayArray(  Character[] characters){
        for(var e : characters) {
            System.out.printf("%c\t",e);
        }
        System.out.println();
    }
    static <T> void displayArrayType(T[] inputArray){
        for(var e : inputArray) {
            System.out.print(e +"\t");
        }
        System.out.println();
    }
}
