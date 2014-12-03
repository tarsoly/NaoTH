package de.naoth.rc.dialogs;

import de.naoth.rc.AbstractDialog;
import de.naoth.rc.Dialog;
import de.naoth.rc.DialogPlugin;
import de.naoth.rc.RobotControl;
import de.naoth.rc.dataformats.JanusImage;
import de.naoth.rc.dialogs.drawings.Canvas;
import de.naoth.rc.dialogs.drawings.Drawable;
import de.naoth.rc.dialogs.drawings.DrawingCollection;
import de.naoth.rc.dialogs.drawings.DrawingOnImage;
import de.naoth.rc.dialogs.drawings.DrawingsContainer;
import de.naoth.rc.manager.DebugDrawingManager;
import de.naoth.rc.manager.ImageManagerBottom;
import de.naoth.rc.manager.ObjectListener;
import de.naoth.rc.manager.ImageManagerTop;
import java.awt.Color;
import java.awt.Graphics2D;
import net.xeoh.plugins.base.annotations.PluginImplementation;
import net.xeoh.plugins.base.annotations.events.PluginLoaded;
import net.xeoh.plugins.base.annotations.injections.InjectPlugin;

/**
 *
 * @author  Thomas
 * @author  Heinrich
 */
public class ImageViewer extends AbstractDialog
{
    
  @PluginImplementation
  public static class Plugin extends DialogPlugin<ImageViewer> {
    @InjectPlugin
    public static RobotControl parent;
    @InjectPlugin
    public static ImageManagerBottom imageManagerBottom;
    //@InjectPlugin
    public static ImageManagerTop imageManagerTop;
    @InjectPlugin
    public static DebugDrawingManager debugDrawingManager;
  }//end Plugin

  private long timestampOfTheLastImage;
  private Drawable fadeOutBox = null;
  
  // listeners
  ImageListenerBottom imageListenerBottom;
  ImageListenerTop imageListenerTop;
  DrawingsListener drawingsListener;

  public ImageViewer()
  {
    initComponents();
    
    this.imageCanvasBottom.setVisible(false);
    this.imageCanvasTop.setVisible(false);
    
    this.timestampOfTheLastImage = 0;
    this.drawingsListener = new DrawingsListener();
    this.imageListenerBottom = new ImageListenerBottom();
    this.imageListenerTop = new ImageListenerTop();
  }

  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the Form Editor.
   */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        imagePanel = new javax.swing.JPanel();
        imageCanvasTop = new de.naoth.rc.dialogs.panels.ImagePanel();
        imageCanvasBottom = new de.naoth.rc.dialogs.panels.ImagePanel();
        jToolBar1 = new javax.swing.JToolBar();
        btReceiveImagesTop = new javax.swing.JToggleButton();
        btReceiveImagesBottom = new javax.swing.JToggleButton();
        btReceiveDrawings = new javax.swing.JToggleButton();
        cbStretch = new javax.swing.JCheckBox();
        cbPreserveAspectRatio = new javax.swing.JCheckBox();
        cbFadeOut = new javax.swing.JCheckBox();
        jLabelFPS = new javax.swing.JLabel();
        jLabelResolution = new javax.swing.JLabel();

        imagePanel.setBackground(java.awt.Color.gray);
        imagePanel.setBorder(javax.swing.BorderFactory.createLineBorder(java.awt.Color.darkGray));
        imagePanel.setPreferredSize(new java.awt.Dimension(320, 240));
        imagePanel.setLayout(new javax.swing.BoxLayout(imagePanel, javax.swing.BoxLayout.PAGE_AXIS));

        imageCanvasTop.setBackground(java.awt.Color.gray);
        imageCanvasTop.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        imageCanvasTop.setOpaque(false);

        javax.swing.GroupLayout imageCanvasTopLayout = new javax.swing.GroupLayout(imageCanvasTop);
        imageCanvasTop.setLayout(imageCanvasTopLayout);
        imageCanvasTopLayout.setHorizontalGroup(
            imageCanvasTopLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 534, Short.MAX_VALUE)
        );
        imageCanvasTopLayout.setVerticalGroup(
            imageCanvasTopLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 114, Short.MAX_VALUE)
        );

        imagePanel.add(imageCanvasTop);

        imageCanvasBottom.setBackground(java.awt.Color.gray);
        imageCanvasBottom.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        imageCanvasBottom.setOpaque(false);

        javax.swing.GroupLayout imageCanvasBottomLayout = new javax.swing.GroupLayout(imageCanvasBottom);
        imageCanvasBottom.setLayout(imageCanvasBottomLayout);
        imageCanvasBottomLayout.setHorizontalGroup(
            imageCanvasBottomLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 534, Short.MAX_VALUE)
        );
        imageCanvasBottomLayout.setVerticalGroup(
            imageCanvasBottomLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 114, Short.MAX_VALUE)
        );

        imagePanel.add(imageCanvasBottom);

        jToolBar1.setFloatable(false);
        jToolBar1.setRollover(true);

        btReceiveImagesTop.setText("Receive Bottom");
        btReceiveImagesTop.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btReceiveImagesTopActionPerformed(evt);
            }
        });
        jToolBar1.add(btReceiveImagesTop);

        btReceiveImagesBottom.setText("Receive Top");
        btReceiveImagesBottom.setFocusable(false);
        btReceiveImagesBottom.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btReceiveImagesBottom.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        btReceiveImagesBottom.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btReceiveImagesBottomActionPerformed(evt);
            }
        });
        jToolBar1.add(btReceiveImagesBottom);

        btReceiveDrawings.setText("Receive Drawings");
        btReceiveDrawings.setFocusable(false);
        btReceiveDrawings.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        btReceiveDrawings.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        btReceiveDrawings.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btReceiveDrawingsActionPerformed(evt);
            }
        });
        jToolBar1.add(btReceiveDrawings);

        cbStretch.setSelected(true);
        cbStretch.setText("stretch image");
        cbStretch.setFocusable(false);
        cbStretch.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        cbStretch.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        cbStretch.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbStretchActionPerformed(evt);
            }
        });
        jToolBar1.add(cbStretch);

        cbPreserveAspectRatio.setSelected(true);
        cbPreserveAspectRatio.setText("keep aspect ratio");
        cbPreserveAspectRatio.setFocusable(false);
        cbPreserveAspectRatio.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        cbPreserveAspectRatio.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        cbPreserveAspectRatio.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbPreserveAspectRatioActionPerformed(evt);
            }
        });
        jToolBar1.add(cbPreserveAspectRatio);

        cbFadeOut.setText("Fade Out");
        cbFadeOut.setToolTipText("Fades out the image so the drawings can be seen better.");
        cbFadeOut.setFocusable(false);
        cbFadeOut.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbFadeOutActionPerformed(evt);
            }
        });
        jToolBar1.add(cbFadeOut);

        jLabelFPS.setFont(new java.awt.Font("Monospaced", 0, 11)); // NOI18N
        jLabelFPS.setText("FPS");

        jLabelResolution.setFont(new java.awt.Font("Monospaced", 0, 11)); // NOI18N
        jLabelResolution.setText("- x - ");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jToolBar1, javax.swing.GroupLayout.DEFAULT_SIZE, 562, Short.MAX_VALUE)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(jLabelResolution, javax.swing.GroupLayout.PREFERRED_SIZE, 65, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabelFPS, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(imagePanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jToolBar1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(imagePanel, javax.swing.GroupLayout.DEFAULT_SIZE, 234, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabelFPS)
                    .addComponent(jLabelResolution)))
        );
    }// </editor-fold>//GEN-END:initComponents
  private void btReceiveImagesTopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btReceiveImagesTopActionPerformed

    if (btReceiveImagesTop.isSelected())
    {
      this.imageCanvasBottom.setVisible(true);
      Plugin.imageManagerBottom.addListener(this.imageListenerBottom);
    }
    else
    {
      this.imageCanvasBottom.setVisible(false);
      Plugin.imageManagerBottom.removeListener(this.imageListenerBottom);
    }

  }//GEN-LAST:event_btReceiveImagesTopActionPerformed

  private void cbPreserveAspectRatioActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbPreserveAspectRatioActionPerformed
    this.imageCanvasBottom.setKeepAspectRatio(this.cbPreserveAspectRatio.isSelected());
    this.imageCanvasTop.setKeepAspectRatio(this.cbPreserveAspectRatio.isSelected());
  }//GEN-LAST:event_cbPreserveAspectRatioActionPerformed

  private void cbStretchActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbStretchActionPerformed
    this.imageCanvasBottom.setStretchImage(this.cbStretch.isSelected());
    this.imageCanvasTop.setStretchImage(this.cbStretch.isSelected());
  }//GEN-LAST:event_cbStretchActionPerformed

  private void btReceiveDrawingsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btReceiveDrawingsActionPerformed
      if (this.btReceiveDrawings.isSelected()) {
          if (Plugin.parent.checkConnected()) {
              Plugin.debugDrawingManager.addListener(this.drawingsListener);
              this.imageCanvasBottom.setShowDrawings(true);
              this.imageCanvasTop.setShowDrawings(true);
          } else {
              this.btReceiveImagesTop.setSelected(false);
          }
      } else {
          Plugin.debugDrawingManager.removeListener(this.drawingsListener);
          this.imageCanvasBottom.setShowDrawings(false);
          this.imageCanvasTop.setShowDrawings(false);
      }
  }//GEN-LAST:event_btReceiveDrawingsActionPerformed

  private void btReceiveImagesBottomActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_btReceiveImagesBottomActionPerformed
  {//GEN-HEADEREND:event_btReceiveImagesBottomActionPerformed
    
    if (this.btReceiveImagesBottom.isSelected())
    {
      this.imageCanvasTop.setVisible(true);
      Plugin.imageManagerTop.addListener(this.imageListenerTop);
    }
    else
    {
      this.imageCanvasTop.setVisible(false);
      Plugin.imageManagerTop.removeListener(this.imageListenerTop);
    }
    
  }//GEN-LAST:event_btReceiveImagesBottomActionPerformed

    private void cbFadeOutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbFadeOutActionPerformed
        if(this.cbFadeOut.isSelected()) {
            this.fadeOutBox = new ImageOverlayDrawing(640, 480, new Color(255,255,255,128));
        } else {
            this.fadeOutBox = null;
        }
    }//GEN-LAST:event_cbFadeOutActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JToggleButton btReceiveDrawings;
    private javax.swing.JToggleButton btReceiveImagesBottom;
    private javax.swing.JToggleButton btReceiveImagesTop;
    private javax.swing.JCheckBox cbFadeOut;
    private javax.swing.JCheckBox cbPreserveAspectRatio;
    private javax.swing.JCheckBox cbStretch;
    private de.naoth.rc.dialogs.panels.ImagePanel imageCanvasBottom;
    private de.naoth.rc.dialogs.panels.ImagePanel imageCanvasTop;
    private javax.swing.JPanel imagePanel;
    private javax.swing.JLabel jLabelFPS;
    private javax.swing.JLabel jLabelResolution;
    private javax.swing.JToolBar jToolBar1;
    // End of variables declaration//GEN-END:variables


  private void updateResolution(int x, int y)
  {
    this.jLabelResolution.setText(x + "x" + y);
  }

  private void updateFPS()
  {
    long currentTime = System.currentTimeMillis();
    double fps = 1000.0 / ((double) (currentTime - this.timestampOfTheLastImage));
    String info = String.format("%4.1f fps", fps);
    this.jLabelFPS.setText(info);
    this.timestampOfTheLastImage = currentTime;
  }

  class DrawingsListener implements ObjectListener<DrawingsContainer>
  {
    @Override
    public void newObjectReceived(DrawingsContainer objectList)
    {
      if (objectList != null)
      {
        ImageViewer.this.imageCanvasBottom.getDrawingList().clear();
        ImageViewer.this.imageCanvasTop.getDrawingList().clear();
        
        // Deprecated
        DrawingCollection drawingCollection = objectList.get(DrawingOnImage.class);
        if (drawingCollection != null) {
          ImageViewer.this.imageCanvasBottom.getDrawingList().add(drawingCollection);
        }
        
        if(ImageViewer.this.fadeOutBox != null) {
            ImageViewer.this.imageCanvasTop.getDrawingList().add(fadeOutBox);
            ImageViewer.this.imageCanvasBottom.getDrawingList().add(fadeOutBox);
        }
        
        Canvas canvasTop = objectList.get("ImageTop");
        if (canvasTop != null) {
          ImageViewer.this.imageCanvasTop.getDrawingList().add(canvasTop);
        }
        
        Canvas canvasBottom = objectList.get("ImageBottom");
        if (canvasTop != null) {
          ImageViewer.this.imageCanvasBottom.getDrawingList().add(canvasBottom);
        }
        
        repaint();
      }
    }//end newObjectReceived
    
    @Override
    public void errorOccured(String cause)
    {
      ImageViewer.this.btReceiveDrawings.setSelected(false);
      ImageViewer.Plugin.debugDrawingManager.removeListener(this);
    }
  }//end class DrawingsListener

  private class ImageListenerBottom implements ObjectListener<JanusImage>
  {
    @Override
    public void newObjectReceived(JanusImage object)
    {
      if(object == null) return;
      ImageViewer.this.imageCanvasBottom.setImage(object.getRgb());
      ImageViewer.this.imageCanvasBottom.repaint();

      updateResolution(object.getRgb().getWidth(), object.getRgb().getHeight());
      updateFPS();
    }

    @Override
    public void errorOccured(String cause)
    {
      ImageViewer.this.btReceiveImagesBottom.setSelected(false);
      ImageViewer.this.imageCanvasBottom.setVisible(false);
      ImageViewer.Plugin.imageManagerBottom.removeListener(this);
    }
  }//end ImageListener
  
  private class ImageListenerTop implements ObjectListener<JanusImage>
  {
    @Override
    public void newObjectReceived(JanusImage object)
    {
      if(object == null) return;
      ImageViewer.this.imageCanvasTop.setImage(object.getRgb());
      ImageViewer.this.imageCanvasTop.repaint();
    }

    @Override
    public void errorOccured(String cause)
    {
      ImageViewer.this.btReceiveImagesTop.setSelected(false);
      ImageViewer.this.imageCanvasTop.setVisible(false);
      ImageViewer.Plugin.imageManagerTop.removeListener(this);
    }
  }//end SecondaryImageListener
  
  class ImageOverlayDrawing implements Drawable
  {
    private final Color color;
    private final int width;
    private final int height;
    
    ImageOverlayDrawing(int width, int height, Color color) {
        this.width = width;
        this.height = height;
        this.color = color;
    }
            
    @Override
    public void draw(Graphics2D g2d) {
        g2d.setColor(color);
        g2d.fillRect(0, 0, width, height);
    }
  }

  @Override
  public void dispose()
  {
    Plugin.imageManagerBottom.removeListener(this.imageListenerBottom);
    Plugin.debugDrawingManager.removeListener(this.drawingsListener);
    this.btReceiveImagesTop.setSelected(false);
    this.btReceiveImagesBottom.setSelected(false);
    this.btReceiveDrawings.setSelected(false);
  }
}//end class ImageViewer

