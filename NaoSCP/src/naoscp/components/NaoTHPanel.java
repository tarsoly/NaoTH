/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package naoscp.components;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import naoscp.tools.Config;
import naoscp.tools.FileUtils;
import naoscp.tools.NaoSCPException;
import naoscp.tools.SwingTools;


/**
 *
 * @author Heinrich Mellmann
 */
public class NaoTHPanel extends javax.swing.JPanel {

    File naothProjectFile = null;
    
    /**
     * Creates new form NaoTHPanel
     */
    public NaoTHPanel() {
        initComponents();
    }
    
    public void setEnabledAll(boolean v) {
        SwingTools.setEnabled(this, v);
    }
    
    public void setProperties(Properties config) {
        updateForm(new File(config.getProperty("naoscp.naothsoccerpath", "../NaoTHSoccer")));
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jSettingsPanel = new javax.swing.JPanel();
        jLabel3 = new javax.swing.JLabel();
        jColorBox = new javax.swing.JComboBox();
        jLabel2 = new javax.swing.JLabel();
        jTeamNumber = new javax.swing.JTextField();
        jLabel4 = new javax.swing.JLabel();
        jSchemeBox = new javax.swing.JComboBox();
        jButtonRefreshData = new javax.swing.JButton();
        jDirPathLabel = new javax.swing.JLabel();
        jDirChooser = new javax.swing.JButton();
        jLabel24 = new javax.swing.JLabel();
        jTeamCommPort = new javax.swing.JTextField();
        cbCopyLib = new javax.swing.JCheckBox();
        cbCopyExe = new javax.swing.JCheckBox();
        cbCopyConfig = new javax.swing.JCheckBox();
        playerNumberPanel = new naoscp.components.PlayerNumberPanel();

        jSettingsPanel.setBackground(new java.awt.Color(204, 204, 255));

        jLabel3.setText("Color:");

        jColorBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "red", "blue" }));
        jColorBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jColorBoxActionPerformed(evt);
            }
        });

        jLabel2.setText("TeamNr:");

        jTeamNumber.setText("4");
        jTeamNumber.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTeamNumberActionPerformed(evt);
            }
        });

        jLabel4.setText("Scheme:");

        jSchemeBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "n/a" }));

        jButtonRefreshData.setText("Refresh");
        jButtonRefreshData.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonRefreshDataActionPerformed(evt);
            }
        });

        jDirPathLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        jDirPathLabel.setText("Set directory to {RepDir}/NaoTHSoccer");
        jDirPathLabel.setToolTipText("NaoTHSoccer project directory");

        jDirChooser.setText("...");
        jDirChooser.setActionCommand("jDirChoose");
        jDirChooser.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jDirChooserPerformed(evt);
            }
        });

        jLabel24.setText("TeamComm:");

        jTeamCommPort.setColumns(10);
        jTeamCommPort.setText("10400");

        javax.swing.GroupLayout jSettingsPanelLayout = new javax.swing.GroupLayout(jSettingsPanel);
        jSettingsPanel.setLayout(jSettingsPanelLayout);
        jSettingsPanelLayout.setHorizontalGroup(
            jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jSettingsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jSettingsPanelLayout.createSequentialGroup()
                        .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel4)
                            .addComponent(jLabel3, javax.swing.GroupLayout.Alignment.TRAILING))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(jSettingsPanelLayout.createSequentialGroup()
                                .addComponent(jColorBox, javax.swing.GroupLayout.PREFERRED_SIZE, 89, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jLabel2)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTeamNumber, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jLabel24)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jTeamCommPort, javax.swing.GroupLayout.PREFERRED_SIZE, 63, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(jSchemeBox, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jButtonRefreshData, javax.swing.GroupLayout.DEFAULT_SIZE, 80, Short.MAX_VALUE)
                        .addGap(4, 4, 4))
                    .addGroup(jSettingsPanelLayout.createSequentialGroup()
                        .addComponent(jDirChooser, javax.swing.GroupLayout.PREFERRED_SIZE, 45, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jDirPathLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jSettingsPanelLayout.setVerticalGroup(
            jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jSettingsPanelLayout.createSequentialGroup()
                .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jDirChooser, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jDirPathLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jSettingsPanelLayout.createSequentialGroup()
                        .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel4, javax.swing.GroupLayout.PREFERRED_SIZE, 17, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jSchemeBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jSettingsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jColorBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel2)
                            .addComponent(jTeamNumber, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel24)
                            .addComponent(jTeamCommPort, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel3)))
                    .addComponent(jButtonRefreshData, javax.swing.GroupLayout.PREFERRED_SIZE, 46, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        cbCopyLib.setText("copyLibNaoSMAL");
        cbCopyLib.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                cbCopyLibItemStateChanged(evt);
            }
        });

        cbCopyExe.setSelected(true);
        cbCopyExe.setText("copyNaoTH(exe)");
        cbCopyExe.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                cbCopyExeItemStateChanged(evt);
            }
        });

        cbCopyConfig.setText("copyConfig");
        cbCopyConfig.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                cbCopyConfigItemStateChanged(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jSettingsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(cbCopyExe)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(cbCopyConfig)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(cbCopyLib)
                .addGap(0, 0, Short.MAX_VALUE))
            .addComponent(playerNumberPanel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jSettingsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(cbCopyExe)
                    .addComponent(cbCopyConfig)
                    .addComponent(cbCopyLib))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(playerNumberPanel, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void cbCopyLibItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_cbCopyLibItemStateChanged
        
    }//GEN-LAST:event_cbCopyLibItemStateChanged

    private void cbCopyExeItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_cbCopyExeItemStateChanged
        
    }//GEN-LAST:event_cbCopyExeItemStateChanged

    private void cbCopyConfigItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_cbCopyConfigItemStateChanged
        
    }//GEN-LAST:event_cbCopyConfigItemStateChanged

    private void jDirChooserPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jDirChooserPerformed
        JFileChooser chooser = new JFileChooser();
        chooser.setCurrentDirectory(new java.io.File("."));
        chooser.setDialogTitle("Select NaoController Directory");
        chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        chooser.setAcceptAllFileFilterUsed(false);
        if(chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION)
        {
            updateForm(chooser.getSelectedFile());
        }
    }//GEN-LAST:event_jDirChooserPerformed

    private void jButtonRefreshDataActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonRefreshDataActionPerformed
        updateForm(naothProjectFile);
    }//GEN-LAST:event_jButtonRefreshDataActionPerformed

    private void jTeamNumberActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTeamNumberActionPerformed
        this.jTeamCommPort.setText("10" + this.jTeamNumber.getText() + "00");
    }//GEN-LAST:event_jTeamNumberActionPerformed

    private void jColorBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jColorBoxActionPerformed

    }//GEN-LAST:event_jColorBoxActionPerformed

    private void updateForm(File projectFile)
    {
        if(!projectFile.isDirectory()) {
            return;
        }
        
        naothProjectFile = projectFile;
        jDirPathLabel.setText(naothProjectFile.getAbsolutePath());
        
        // load the defaults for the configs
        File configDir = new File(naothProjectFile, "Config");
        loadPlayerCfg(configDir);
        loadConfigSchemes(configDir);
        loadTeamCommCfg(configDir);

        playerNumberPanel.setRobots(configDir);
        
        // check for the binaries
        if(new File(naothProjectFile, CopyConfigAction.localBinPath + "/naoth").exists()) {
            cbCopyExe.setEnabled(true);
        } else {
            cbCopyExe.setEnabled(false);
            cbCopyExe.setSelected(false);
        }
        if(new File(naothProjectFile, CopyConfigAction.localBinPath + "/libnaosmal.so").exists()) {
            cbCopyLib.setEnabled(true);
        } else {
            cbCopyLib.setEnabled(false);
            cbCopyLib.setSelected(false);
        }
    }
    
   /**
   * populates the Schemes-Dropdown with the Schemes found in the schemedir
   *
   * @return
   */
  private boolean loadConfigSchemes(File configPath)
  {
    if( ! configPath.isDirectory())
    {
      return false;
    }

    File schemePath = new File(configPath, "scheme");
    if( ! schemePath.isDirectory())
    {
      return false;
    }

    File files[] = schemePath.listFiles();
    Arrays.sort(files);
    this.jSchemeBox.removeAllItems();
    this.jSchemeBox.addItem("n/a");
    for(int i = 0; i < files.length; i++)
    {
      if(files[i].isDirectory())
      {
        this.jSchemeBox.addItem(files[i].getName());
      }
    }
    this.jSchemeBox.setSelectedIndex(0);
    return true;
  }//end readConfigSchemes
  
  
  private void loadPlayerCfg(File configFile)
  {
    try {
        Config playerCfg = new Config("player");
        playerCfg.readFromFile(new File(configFile, "general/player.cfg"));

        String teamColor = playerCfg.values.get("TeamColor");
        if(teamColor != null) {
            jColorBox.setSelectedItem(teamColor);
        }

        String teamNumber = playerCfg.values.get("TeamNumber");
        if(teamNumber != null) {
            jTeamNumber.setText(teamNumber);
        }
    } catch(IOException ex) {
        Logger.getGlobal().log(Level.SEVERE, "Could not load player.cfg\n" + ex.getMessage());
        ex.printStackTrace(System.err);
    }
  }
  
  private Config getPlayerCfg()
  {
    Config cfg = new Config("player");
    cfg.values.put("TeamColor", jColorBox.getSelectedItem().toString());
    cfg.values.put("TeamNumber", jTeamNumber.getText());
    return cfg;
  }
  
  private void loadTeamCommCfg(File configFile)
  {
      try {
          Config cfg = new Config("teamcomm");
            cfg.readFromFile(new File(configFile, "general/teamcomm.cfg"));

            String port = cfg.values.get("port");
            if(port != null) {
                jTeamCommPort.setText(port);
            }
      } catch(IOException ex) {
          Logger.getGlobal().log(Level.SEVERE, "Could not load teamcomm.cfg\n" + ex.getMessage());
          ex.printStackTrace(System.err);
      }
  }
  
  
  private Config getTeamCommCfg()
  {
    Config cfg = new Config("teamcomm");
    cfg.values.put("port", jTeamCommPort.getText());
    return cfg;
  }
  
  public CopyConfigAction getAction() throws NaoSCPException {
      
      if( this.naothProjectFile == null || 
          !this.naothProjectFile.exists() || 
          !this.naothProjectFile.isDirectory())
      {
          //Logger.getGlobal().log(Level.WARNING, "No valid NaoTH project directory specified.");
          throw new NaoSCPException("No valid NaoTH project directory specified.");
      }
      return new CopyConfigAction(naothProjectFile);
  }
  
    public class CopyConfigAction {

        private final static String deployConfigPath = "/home/nao/naoqi/Config";
        private final static String deployBinPath = "/home/nao/bin";

        private final static String localConfigPath = "/Config";
        private final static String localBinPath = "/dist/Nao";

        private final File localConfigDir;
        private final File localBinDir;

        public CopyConfigAction(File projectDir) {
            this.localConfigDir = new File(projectDir, localConfigPath);
            this.localBinDir = new File(projectDir, localBinPath);
        }

        public void run(File deployDir) throws NaoSCPException 
        {
            // HACK: check if there is anything to be done
            if(!cbCopyLib.isSelected() && 
               !cbCopyExe.isSelected() &&
               !cbCopyConfig.isSelected()) 
            {
                throw new NaoSCPException("Set up deploy directory: no action selected");
            }
            
            Logger.getGlobal().log(Level.INFO, "Set up deploy directory '" + deployDir + "'");
            File deployBinDir = new File(deployDir, deployBinPath);
            deployBinDir.mkdirs();

            if (cbCopyLib.isSelected()) {
                File src = new File(localBinDir, "libnaosmal.so");
                File dst = new File(deployBinDir, "libnaosmal.so");
                FileUtils.copyFiles(src, dst);
            }

            if (cbCopyExe.isSelected()) {
                File src = new File(localBinDir, "naoth");
                File dst = new File(deployBinDir, "naoth");
                FileUtils.copyFiles(src, dst);
            }

            // copy Config
            if(cbCopyConfig.isSelected())
            {
                File deployConfigDir = new File(deployDir, deployConfigPath);
                deployConfigDir.mkdirs();
                FileUtils.copyFiles(localConfigDir, deployConfigDir);

                // the "private" folder should always be empty
                File privateFolder = new File(deployConfigDir, "private");
                FileUtils.deleteDir(privateFolder);
                if (!privateFolder.mkdir()) {
                    //Logger.getGlobal().log(Level.SEVERE, "Could not create empty \"private\" folder: " + privateFolder.getPath());
                    throw new NaoSCPException("Could not create empty \"private\" folder: " + privateFolder.getPath());
                }

                try {
                    //write the config files
                    getTeamCommCfg().writeToFile(new File(privateFolder, "teamcomm.cfg"));
                    getPlayerCfg().writeToFile(new File(privateFolder, "player.cfg"));
                    writeScheme(jSchemeBox.getSelectedItem().toString(),new File(deployConfigDir, "scheme.cfg"));

                } catch(IOException ex) {
                    //Logger.getGlobal().log(Level.SEVERE, "Could not write config\n" + ex.getMessage());
                    //ex.printStackTrace(System.err);
                    throw new NaoSCPException("Could not write config\n" + ex.getMessage());
                }
            }
        }
        
        // HACK: scheme should be a .cfg as everything else
        private void writeScheme(String scheme, File schemeCfg)
        {
          if(scheme != null && !scheme.isEmpty() && !"n/a".equals(scheme))
          {
            try
            {
              FileUtils.writeToFile(scheme, schemeCfg);
            }
            catch(IOException ioe)
            {
                Logger.getGlobal().log(Level.SEVERE, "I/O Error in writeScheme- {0}" + ioe.toString());
            }
          }
        }
    }
  

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JCheckBox cbCopyConfig;
    private javax.swing.JCheckBox cbCopyExe;
    private javax.swing.JCheckBox cbCopyLib;
    private javax.swing.JButton jButtonRefreshData;
    private javax.swing.JComboBox jColorBox;
    private javax.swing.JButton jDirChooser;
    private javax.swing.JLabel jDirPathLabel;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel24;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JComboBox jSchemeBox;
    private javax.swing.JPanel jSettingsPanel;
    private javax.swing.JTextField jTeamCommPort;
    private javax.swing.JTextField jTeamNumber;
    private naoscp.components.PlayerNumberPanel playerNumberPanel;
    // End of variables declaration//GEN-END:variables
}
