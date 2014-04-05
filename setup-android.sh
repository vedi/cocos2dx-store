ANDROID_PATH=./android
SUBMODULE_PATH=./submodules/android-store/SoomlaAndroidStore
GOOGLE_PLAY_SUBMODULE_PATH=$SUBMODULE_PATH/../submodules/android-store-google-play/

ANDROID_MANIFEST_FILE=AndroidManifest.xml
PROJECT_PROPERTIES_FILE=project.properties
LOCAL_PROPERTIES_FILE=local.properties

if [ -z "$1" ]
then
  echo "ERROR: please, provide target as a first param"
  exit 1
fi

TARGET=$1

if [ ! -e "$SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE" ]
then
  echo "generate properties for submodule"
  echo "android.library=true" >> "$SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE"
  echo "android.library.reference.1=../submodules/android-store-google-play/" >> "$SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE"
fi

if [ ! -e "$GOOGLE_PLAY_SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE" ]
then
  echo "generate properties for submodule"
  echo "android.library=true" >> "$GOOGLE_PLAY_SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE"
fi

if [ ! -e "$GOOGLE_PLAY_SUBMODULE_PATH/$ANDROID_MANIFEST_FILE" ]
then
  echo "generate Android Manifest for submodule"
  echo "<?xml version=\"1.0\" encoding=\"utf-8\"?>" >> "$GOOGLE_PLAY_SUBMODULE_PATH/$ANDROID_MANIFEST_FILE"
  echo "<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\"" >> "$GOOGLE_PLAY_SUBMODULE_PATH/$ANDROID_MANIFEST_FILE"
  echo "  package=\"com.soomla.store\">" >> "$GOOGLE_PLAY_SUBMODULE_PATH/$ANDROID_MANIFEST_FILE"
  echo "</manifest>" >> "$GOOGLE_PLAY_SUBMODULE_PATH/$ANDROID_MANIFEST_FILE"
fi

android update project -p $ANDROID_PATH -t $TARGET
android update project -p $SUBMODULE_PATH -t $TARGET
android update project -p $GOOGLE_PLAY_SUBMODULE_PATH -t $TARGET

