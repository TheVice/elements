package com.yegorov.alexey.elements.api;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.Vector;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class Unzip {

    private ZipFile zipFile;

    public Unzip(String path_to_zip) {

        zipFile = openZipFile(path_to_zip);
    }

    public Vector<String> listFiles() {

        return listZip(zipFile);
    }

    public void extractFile(String source, String destination) {

        try {

            /*File file = new File(destination);
            if (!file.exists()) {

                try {
                    file.createNewFile();
                }
                catch (IOException exc) {

                    exc.printStackTrace();
                    throw new RuntimeException("Unable to create " + destination);
                }
            }*/

            int index = destination.lastIndexOf("/");
            String folderPath = destination.substring(0, index);
            File file = new File(folderPath);
            if (!file.exists()) {

                file.mkdirs();
            }

            extractEntryInto(zipFile, source, destination);
        } catch (RuntimeException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to extract " + source + " into " + destination);
        }
    }

    public void close() {

        closeZipFile(zipFile);
        zipFile = null;
    }

    public static ZipFile openZipFile(String fileName) {

        ZipFile zipFile = null;

        try {

            zipFile = new ZipFile(fileName);
        } catch (IOException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to open zip file " + fileName);
        }

        return zipFile;
    }

    public static Vector<String> listZip(ZipFile zipFile) {

        Vector<String> files = new Vector<String>(1024);
        Enumeration<ZipEntry> listOfFiles = (Enumeration<ZipEntry>) zipFile.entries();

        while(listOfFiles.hasMoreElements()) {

            files.add(listOfFiles.nextElement().getName());
        }

        return files;
    }

    public static void writeFile(InputStream source, String destination, int bufferLength) throws IOException {

        FileOutputStream fileOutputStream = null;
        try {

            fileOutputStream = new FileOutputStream(destination);
        } catch (FileNotFoundException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to extract into " + destination);
        }

        byte buffer[] = new byte[bufferLength];
        int readed = 0;

        while (-1 != (readed = source.read(buffer))) {

            fileOutputStream.write(buffer, 0, readed);
        }

        fileOutputStream.close();
    }

    public static void extractEntryInto(ZipFile zipFile, String entryName, String destination) {

        ZipEntry arEntry = null;
        try {

            arEntry = zipFile.getEntry(entryName);
        } catch (IllegalStateException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to find entry " + entryName + " in zip file " + zipFile.getName());
        }

        InputStream input = null;
        try {

            input = zipFile.getInputStream(arEntry);
        } catch (IOException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to get input stream for entry " + entryName);
        }

        try {

            writeFile(input, destination, 4 * 1024 * 1024);
        } catch (IOException exc) {

            exc.printStackTrace();
            throw new RuntimeException("Unable to extract entry " + entryName + " from " + zipFile.getName() + " into " + destination);
        }

        try {

            input.close();
        } catch (IOException exc) {

            exc.printStackTrace();
        }
    }

    public static void closeZipFile(ZipFile zipFile) {

        try {

            zipFile.close();
        } catch (IOException exc) {

            exc.printStackTrace();
        }
    }

}
