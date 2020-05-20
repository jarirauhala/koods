package fi.lut.shoppinglist;

import java.util.ArrayList;

public class DataBase {

    private ArrayList<String> testList = new ArrayList<String>();

    public DataBase() {
        testList.add("init1");
    }

    public ArrayList<String> getData() {
        return testList;
    }

    public void addNewItem(String item) {
        testList.add(item);
    }
}
