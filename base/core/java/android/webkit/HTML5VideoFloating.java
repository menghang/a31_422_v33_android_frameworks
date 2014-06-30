
package android.webkit;

//import android.Manifest.permission;
//import android.content.pm.PackageManager;
import android.content.Context;
//import android.media.MediaPlayer;
//import android.media.Metadata;
//import android.view.Gravity;
//import android.view.MotionEvent;
//import android.view.SurfaceHolder;
//import android.view.SurfaceView;
//import android.view.View;
//import android.view.ViewGroup;
//import android.widget.FrameLayout;
//import android.widget.MediaController;
//import android.widget.MediaController.MediaPlayerControl;
//import android.os.PowerManager;

import android.util.Log;


/**
 * @hide This is only used by the browser
 */
public class HTML5VideoFloating {
	private final String TAG = "HTML5VideoFloating";
	private int mBreakPointPositon;
	//protected Uri mUri;
    //protected Map<String, String> mHeaders;
	private String mUriPath;
	private HTML5VideoViewProxy mProxy;
	
	HTML5VideoFloating(Context context, int videoLayerId, int position, boolean skipPrepare) {
        //mVideoSurfaceView = new VideoSurfaceView(context);
        //mVideoWidth = 0;
        //mVideoHeight = 0;
        //init(videoLayerId, position, skipPrepare);
		mBreakPointPositon = position;
    }
    
	public void setVideoURI(String uri, HTML5VideoViewProxy proxy) {
        // When switching players, surface texture will be reused.
        //mUri = Uri.parse(uri);
        //mHeaders = generateHeaders(uri, proxy);
		mUriPath = uri;
		Log.v(TAG, "Path:"+uri);
    }
	
	private final WebChromeClient.CustomViewCallback mCallback =
	        new WebChromeClient.CustomViewCallback() {
		        @Override
		        public void onCustomViewHidden() {
		            // It listens to SurfaceHolder.Callback.SurfaceDestroyed event
		            // which happens when the video view is detached from its parent
		            // view. This happens in the WebChromeClient before this method
		            // is invoked.

		            // Re enable plugin views.
		            mProxy.getWebView().getViewManager().showAll();
		            // Don't show the controller after exiting the full screen.
		            // Continue the inline mode playing if necessary.
		            mProxy.dispatchOnStopFullScreen(false);
		            mProxy = null;
		        }
	        };
	
	public void enterFullScreenVideoState(int layerId,
            HTML5VideoViewProxy proxy, WebViewClassic webView) {
		mProxy = proxy;
        WebChromeClient client = webView.getWebChromeClient();
        if (client != null) {
            client.onShowFloatingVideoView(mUriPath, mBreakPointPositon, mCallback);
        }
    }
}
