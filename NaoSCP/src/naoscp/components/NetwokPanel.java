/*
 * 
 */

package naoscp.components;

/**
 *
 * @author Heinrich Mellmann
 */
public class NetwokPanel extends javax.swing.JPanel {

    /**
     * Creates new form NetwokPanel
     */
    public NetwokPanel() {
        initComponents();
    }

    public static class NetworkConfig
    {
        public static class NetConfig {
            public final String subnet;
            public final String mask;
            public final String broadcast;

            public NetConfig(String subnet, String mask, String broadcast) {
                this.subnet = subnet;
                this.mask = mask;
                this.broadcast = broadcast;
            }
        }
        
        public static class WlanConfig {
            public static enum Encryption {
                WEP, WPA
            }
            public final String ssid;
            public final String key;
            public final Encryption ecryption;

            public WlanConfig(String ssid, String key, Encryption ecryption) {
                this.ssid = ssid;
                this.key = key;
                this.ecryption = ecryption;
            }
        }
        
        private NetConfig lan;
        private NetConfig wlan;
        private WlanConfig wlan_encryption;

        public NetConfig getLan() {
            return lan;
        }

        public NetConfig getWlan() {
            return wlan;
        }

        public WlanConfig getWlan_encryption() {
            return wlan_encryption;
        }
    }
    
    public NetworkConfig getNetworkConfig() {
        NetworkConfig cfg = new NetworkConfig();
        
        cfg.lan = new NetworkConfig.NetConfig(
                this.subnetFieldLAN.getText(),
                this.netmaskFieldLAN.getText(),
                this.broadcastFieldLAN.getText()
        );
        
        cfg.wlan = new NetworkConfig.NetConfig(
                this.subnetFieldWLAN.getText(),
                this.netmaskFieldWLAN.getText(),
                this.broadcastFieldWLAN.getText()
        );
        
        NetworkConfig.WlanConfig.Encryption encryption = NetworkConfig.WlanConfig.Encryption.WEP;
        if(this.radioWEP.isSelected()) {
            encryption = NetworkConfig.WlanConfig.Encryption.WEP;
        } else if(this.radioWPA.isSelected()) {
            encryption = NetworkConfig.WlanConfig.Encryption.WPA;
        }
        
        cfg.wlan_encryption = new NetworkConfig.WlanConfig(
                this.wlanSSID.getText(),
                this.wlanKey.getText(),
                encryption
        );
        
        return cfg;
    }
    
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroupWepWpa = new javax.swing.ButtonGroup();
        jLabel13 = new javax.swing.JLabel();
        jLabel1 = new javax.swing.JLabel();
        jLabel20 = new javax.swing.JLabel();
        jLabel22 = new javax.swing.JLabel();
        subnetFieldLAN = new javax.swing.JTextField();
        netmaskFieldLAN = new javax.swing.JTextField();
        broadcastFieldLAN = new javax.swing.JTextField();
        jLabel14 = new javax.swing.JLabel();
        jLabel19 = new javax.swing.JLabel();
        jLabel21 = new javax.swing.JLabel();
        jLabel23 = new javax.swing.JLabel();
        subnetFieldWLAN = new javax.swing.JTextField();
        netmaskFieldWLAN = new javax.swing.JTextField();
        broadcastFieldWLAN = new javax.swing.JTextField();
        radioWPA = new javax.swing.JRadioButton();
        radioWEP = new javax.swing.JRadioButton();
        jLabel5 = new javax.swing.JLabel();
        wlanSSID = new javax.swing.JTextField();
        jLabel9 = new javax.swing.JLabel();
        wlanKey = new javax.swing.JTextField();

        jLabel13.setText("LAN:");

        jLabel1.setText("SubNet");

        jLabel20.setText("Netmask");

        jLabel22.setText("Broadcast");

        subnetFieldLAN.setText("10.0.4");

        netmaskFieldLAN.setText("255.255.255.0");

        broadcastFieldLAN.setEditable(false);
        broadcastFieldLAN.setText("10.0.4.255");

        jLabel14.setText("WLAN:");

        jLabel19.setText("SubNet");

        jLabel21.setText("Netmask");

        jLabel23.setText("Broadcast");

        subnetFieldWLAN.setText("192.168.13");

        netmaskFieldWLAN.setText("255.255.255.0");

        broadcastFieldWLAN.setEditable(false);
        broadcastFieldWLAN.setText("192.168.13.255");

        buttonGroupWepWpa.add(radioWPA);
        radioWPA.setSelected(true);
        radioWPA.setText("WPA PSK");
        radioWPA.setOpaque(false);

        buttonGroupWepWpa.add(radioWEP);
        radioWEP.setText("WEP");
        radioWEP.setOpaque(false);

        jLabel5.setText("SSID");

        wlanSSID.setText("NAONET");

        jLabel9.setText("WLAN Key");

        wlanKey.setText("a1b0a1b0a1");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel9)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel5)
                        .addGap(221, 221, 221)
                        .addComponent(radioWEP)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(radioWPA)))
                .addGap(30, 30, 30))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(12, 12, 12)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel13)
                        .addGap(365, 365, 365))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel20, javax.swing.GroupLayout.PREFERRED_SIZE, 66, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel1)
                            .addComponent(jLabel22))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                    .addComponent(subnetFieldLAN, javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(netmaskFieldLAN, javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(broadcastFieldLAN, javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(wlanSSID, javax.swing.GroupLayout.Alignment.LEADING))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jLabel21)
                                    .addComponent(jLabel19)
                                    .addComponent(jLabel23)
                                    .addComponent(jLabel14))
                                .addGap(21, 21, 21)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(broadcastFieldWLAN)
                                    .addComponent(subnetFieldWLAN)
                                    .addComponent(netmaskFieldWLAN)))
                            .addComponent(wlanKey))
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel14)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel19)
                            .addComponent(subnetFieldWLAN, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel21)
                            .addComponent(netmaskFieldWLAN, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(broadcastFieldWLAN, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel13)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(subnetFieldLAN, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel1))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel20)
                            .addComponent(netmaskFieldLAN, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel22)
                            .addComponent(broadcastFieldLAN, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel23))))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel5)
                    .addComponent(wlanSSID, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(radioWEP)
                    .addComponent(radioWPA))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel9)
                    .addComponent(wlanKey, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextField broadcastFieldLAN;
    private javax.swing.JTextField broadcastFieldWLAN;
    private javax.swing.ButtonGroup buttonGroupWepWpa;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel14;
    private javax.swing.JLabel jLabel19;
    private javax.swing.JLabel jLabel20;
    private javax.swing.JLabel jLabel21;
    private javax.swing.JLabel jLabel22;
    private javax.swing.JLabel jLabel23;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JTextField netmaskFieldLAN;
    private javax.swing.JTextField netmaskFieldWLAN;
    private javax.swing.JRadioButton radioWEP;
    private javax.swing.JRadioButton radioWPA;
    private javax.swing.JTextField subnetFieldLAN;
    private javax.swing.JTextField subnetFieldWLAN;
    private javax.swing.JTextField wlanKey;
    private javax.swing.JTextField wlanSSID;
    // End of variables declaration//GEN-END:variables
}
