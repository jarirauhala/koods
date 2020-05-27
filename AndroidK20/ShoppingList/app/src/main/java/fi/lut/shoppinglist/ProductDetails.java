package fi.lut.shoppinglist;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

public class ProductDetails extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_product_details);

        System.out.println("OJ90");

        Intent in = getIntent();

        String name = in.getStringExtra("fi.lut.PRODUCT_NAME");
        String price = in.getStringExtra("fi.lut.PRODUCT_PRICE");
        String brand = in.getStringExtra("fi.lut.PRODUCT_BRAND");
        //Bitmap pic = in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE");

        System.out.println("OJ91");


        Bitmap pic = BitmapFactory.decodeByteArray(
                in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE"),
                0,
                in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE").length);

        System.out.println("OJ1");
        //Uri picUri = in.getData();

        System.out.println("OJ90");


        TextView namedisp = (TextView) findViewById(R.id.productNameTextView);
        TextView pricedisp = (TextView) findViewById(R.id.priceTextView);
        TextView branddisp = (TextView) findViewById(R.id.brandTextView);
        ImageView picdisp = (ImageView) findViewById(R.id.detailImageView);

        System.out.println("OJ2");

        namedisp.setText(name);
        pricedisp.setText(price);
        branddisp.setText(brand);
        //picdisp.setImageURI(picUri);

        picdisp.setImageBitmap(pic);

    }
}
