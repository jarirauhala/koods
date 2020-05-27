package fi.lut.shoppinglist;

import android.graphics.Bitmap;
import android.net.Uri;

public class ListItem {

    public String mAmount;
    public String mProductName = "";
    public String mBrand = "";
    public String mPrice = "";
    public Bitmap mPic;


    public ListItem(String amount, String name, String brand, String price, Bitmap picture) {
        mAmount = amount;
        mProductName = name;
        mBrand = brand;
        mPrice = price;
        mPic = picture;
    }
}
