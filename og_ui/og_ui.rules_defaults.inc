<?php

/**
 * Implements hook_default_rules_configuration().
 */
function og_ui_default_rules_configuration() {
  $items = array();
  $items['rules_member_subscribe'] = entity_import('rules_config', '{ "rules_member_subscribe" : {
      "LABEL" : "Member subscribe",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_ui_subscribe_member" ],
      "IF" : [ { "data_is" : { "data" : [ "state" ], "value" : "active" } } ],
      "DO" : [
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request was approved for \'[group:label]\'",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \'[group:label]\' located at [group:url]",
            "from" : ""
          }
        }
      ]
    }
  }');
  $items['rules_member_subscribe_pending'] = entity_import('rules_config', '{ "rules_member_subscribe_pending" : {
      "LABEL" : "Member subscribe (pending approval)",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : [ "og_ui_subscribe_member" ],
      "IF" : [ { "data_is" : { "data" : [ "state" ], "value" : "pending" } } ],
      "DO" : [
        { "mail" : {
            "to" : "[account:mail]",
            "subject" : "Your membership request is pending for \'[group:label]\'",
            "message" : "[user:name],\\r\\n\\r\\nYour membership to \'[group:label]\' located at [group:url] is pending approval.",
            "from" : ""
          }
        },
        { "og_get_managers_from_group" : {
            "USING" : { "group" : [ "group" ] },
            "PROVIDE" : { "group_manager" : { "group_manager" : "Group manager" } }
          }
        },
        { "mail" : {
            "to" : [ "group-manager:mail" ],
            "subject" : "Membership request for \'[group:label]\' from [account:name]",
            "message" : "[group-manager:name],\\r\\n\\r\\n[user:name] is requesting membership to \'[group:label]\' located at [group:url]\\r\\n\\r\\n!request",
            "from" : ""
          }
        }
      ]
    }
  }');
  return $items;
}