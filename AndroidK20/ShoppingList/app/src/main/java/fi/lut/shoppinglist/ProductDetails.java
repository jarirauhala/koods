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

        Intent in = getIntent();

        String amount = in.getStringExtra("fi.lut.PRODUCT_AMOUNT");
        String name = in.getStringExtra("fi.lut.PRODUCT_NAME");
        String price = in.getStringExtra("fi.lut.PRODUCT_PRICE");
        String brand = in.getStringExtra("fi.lut.PRODUCT_BRAND");

        Bitmap pic = BitmapFactory.decodeByteArray(
                in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE"),
                0,
                in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE").length);

        TextView amountdisp = (TextView) findViewById(R.id.amountTextView);
        TextView namedisp = (TextView) findViewById(R.id.productNameTextView);
        TextView pricedisp = (TextView) findViewById(R.id.priceTextView);
        TextView branddisp = (TextView) findViewById(R.id.brandTextView);
        ImageView picdisp = (ImageView) findViewById(R.id.detailImageView);

        amountdisp.setText(amount);
        namedisp.setText(name);
        pricedisp.setText(price);
        branddisp.setText(brand);

        picdisp.setImageBitmap(pic);
    }
}
