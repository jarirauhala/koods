package fi.lut.shoppinglist;

import android.graphics.Bitmap;
import android.net.Uri;

public class ListItem {

    public String mProductName = "";
    public String mBrand = "";
    public String mPrice = "";
    //public Uri mPictureURI;
    public Bitmap mPic;
    // todo: picture


    public ListItem(String name, String brand, String price, Bitmap picture) {
        mProductName = name;
        mBrand = brand;
        mPrice = price;
        mPic = picture;
    }
}
