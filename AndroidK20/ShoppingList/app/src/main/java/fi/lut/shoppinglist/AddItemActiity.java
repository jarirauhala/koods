package fi.lut.shoppinglist;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.media.Image;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.URI;

import static android.app.Activity.RESULT_OK;

public class AddItemActiity extends AppCompatActivity {

    Button addImageButton;
    ImageView prevImgView;
    Button addNewItemButton;

    EditText amountTextEdit;
    EditText nameTextEdit;
    EditText brandTextEdit;
    EditText priceTextEdit;

    String mAmount;
    String mName;
    String mBrand;
    String mPrice;
    Uri mPicURI;
    Bitmap mPic;

    private static final int IMAGE_PICK_CODE = 1000;
    private static final int PERMISSION_CODE = 1001;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_item_actiity);

        addImageButton = (Button) findViewById(R.id.addImageButton);
        prevImgView = (ImageView) findViewById(R.id.previewImageView);
        addNewItemButton = (Button) findViewById(R.id.addNewItemButton);

        amountTextEdit = (EditText) findViewById(R.id.amountEditText);
        nameTextEdit = (EditText) findViewById(R.id.productNameEditText);
        brandTextEdit = (EditText) findViewById(R.id.brandEditText);
        priceTextEdit = (EditText) findViewById(R.id.priceEditText);

        mAmount = getIntent().getStringExtra("fi.lut.PRODUCT_AMOUNT");
        mName = getIntent().getStringExtra("fi.lut.PRODUCT_NAME");
        mBrand = getIntent().getStringExtra("fi.lut.PRODUCT_BRAND");
        mPrice = getIntent().getStringExtra("fi.lut.PRODUCT_PRICE");

        // init mPic with default picture
        mPic = BitmapFactory.decodeResource(getResources(), R.drawable.cart);

        addImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // check runtime permission
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                    if (checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED) {
                        String[] permissions = {Manifest.permission.READ_EXTERNAL_STORAGE};
                        requestPermissions(permissions, PERMISSION_CODE);

                    }
                    else { // permission already granted
                        pickImageFromGallery();
                    }
                }
                else {
                    pickImageFromGallery();
                }
            }
        });

        addNewItemButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                mAmount = amountTextEdit.getText().toString();
                mName = nameTextEdit.getText().toString();
                mBrand = brandTextEdit.getText().toString();
                mPrice = priceTextEdit.getText().toString();

                Intent result = new Intent();
                result.putExtra("fi.lut.AMOUNT_INPUT", mAmount);
                result.putExtra("fi.lut.NAME_INPUT", mName);
                result.putExtra("fi.lut.BRAND_INPUT", mBrand);
                result.putExtra("fi.lut.PRICE_INPUT", mPrice);

                // compress image
                ByteArrayOutputStream bs = new ByteArrayOutputStream();
                mPic.compress(Bitmap.CompressFormat.JPEG, 50, bs);
                result.putExtra("fi.lut.PIC_INPUT", bs.toByteArray());

                setResult(RESULT_OK, result);
                finish();
            }
        });
    }


    private void pickImageFromGallery() {
        Intent pickImage = new Intent(Intent.ACTION_PICK);
        pickImage.setType("image/*");
        startActivityForResult(pickImage, IMAGE_PICK_CODE);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case PERMISSION_CODE:{
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    pickImageFromGallery();
                }
                else {
                    Toast.makeText(this, "Permission denied!", Toast.LENGTH_SHORT).show();
                }
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == RESULT_OK && requestCode == IMAGE_PICK_CODE) {
            mPicURI = data.getData();
            //prevImgView.setImageURI(mPicURI);
            try {
                mPic = MediaStore.Images.Media.getBitmap(this.getContentResolver(), mPicURI);
                prevImgView.setImageBitmap(mPic);
            } catch (IOException e) {
                Intent error = new Intent (getApplicationContext(), ProductDetails.class);
                error.putExtra("fi.lut.PRODUCT_NAME", "error in converting to bitmap");
                startActivity(error);
            }

        }
    }
}
